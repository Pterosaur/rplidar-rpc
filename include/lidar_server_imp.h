//
// Created by ganze on 17-3-27.
//

#ifndef RPLIDAR_RPC_LIDAR_SERVER_IMP_H
#define RPLIDAR_RPC_LIDAR_SERVER_IMP_H

#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>
#include <map>
#include <set>
#include <string>
#include <cstdint>
#include <mutex>
#include <atomic>
#include <memory>
#include "device/lidar.h"
#include "lidar.grpc.pb.h"

class lidar_server_imp final :
    public device::lidar_server::Service {
private:
    class lidar_connector {
        friend std::shared_ptr<lidar_connector>;
    private:
        device::handle_lidar        m_lidar_handle;
        bool                        m_is_start;
        std::mutex *                m_visit_mutex;
        std::atomic<std::uint64_t> *m_user_count;
    public:
        lidar_connector(const std::string & conn) {
            m_lidar_handle =
                    device::MakeLidar(device::LIDAR_TYPE::RPLIDARA1M1);
            if (!m_lidar_handle->Init(conn)) {
                throw device::lidar_init_exception(conn + "cannot init");
            }
            m_visit_mutex = new std::mutex;
            m_user_count  = new std::atomic<std::uint64_t>(0);
            m_is_start    = false;
        }
        lidar_connector(lidar_connector && conn) :
            m_visit_mutex(conn.m_visit_mutex) {
            m_lidar_handle = conn.m_lidar_handle;
            m_user_count = conn.m_user_count;
            m_is_start = conn.m_is_start;
        }
        lidar_connector(lidar_connector & ) = delete;
        ~lidar_connector() {
            delete m_visit_mutex;
            delete m_user_count;
        }
        device::lidar_raw_points get_points() {
            std::lock_guard<std::mutex> lock(*m_visit_mutex);
            if ( ! m_is_start) {
                if (m_lidar_handle->Start()) {
                    m_is_start = true;
                }
            }
            size_t  count = 360 * 2;
            return m_lidar_handle->GetData(count);
        }
        bool start() {
            std::lock_guard<std::mutex> lock(*m_visit_mutex);
            if (m_lidar_handle->Start()) {
                m_is_start = true;
                return true;
            }
            return false;
        }
        bool stop() {
            std::lock_guard<std::mutex> lock(*m_visit_mutex);
            if(m_is_start) {
                if (m_lidar_handle->Stop()) {
                    m_is_start = false;
                    return true;
                } else {
                    return false;
                }
            }
            return true;
        }
        std::uint64_t  add_ref() {
            return ++(*m_user_count);
        }
        std::uint64_t remove_ref() {
            return --(*m_user_count);
        }

    };
    struct lidar_visitor {
        friend  std::shared_ptr<lidar_visitor>;
        std::shared_ptr<lidar_connector> m_conn;
        lidar_visitor(std::shared_ptr<lidar_connector> conn)
                : m_conn(conn) {
            m_conn->add_ref();
        }
        ~lidar_visitor() {
            if (0 == m_conn->remove_ref()) {
                m_conn->stop();
            }
        }
    };
    std::mutex                                               m_create_device_mutex;
    std::map<std::string, std::shared_ptr<lidar_connector> > m_lidars;
    std::map<std::string, std::shared_ptr<lidar_visitor> >   m_user_map;
    std::string generator_token() const;
public:
    grpc::Status create(
        grpc::ServerContext * context,
        const device::connect_info * conn,
        device::token * tk);

    grpc::Status start(
        grpc::ServerContext * context,
        const device::token * tk,
        google::protobuf::Empty *
    );

    grpc::Status stop(
        grpc::ServerContext * context,
        const device::token * tk,
        google::protobuf::Empty *
    );

    grpc::Status get_points(
        grpc::ServerContext * context,
        const device::token * tk,
        device::lidar_raw_points *
    );
};

class RunRPCServerImp{
private:
    lidar_server_imp m_imp;
    std::unique_ptr<grpc::Server> server;
    grpc::ServerBuilder builder;

    void Run(std::string address ) {
        builder.AddListeningPort(address, grpc::InsecureServerCredentials());
        builder.RegisterService(&m_imp);
        server = builder.BuildAndStart();
    }
    RunRPCServerImp() {
    }
    ~RunRPCServerImp() {
        server->Shutdown();
    }
public:

    static void StartRPCServer(std::string address) {
        static RunRPCServerImp server;
        server.Run(address);
    }
};

#endif //RPLIDAR_RPC_LIDAR_SERVER_IMP_H
