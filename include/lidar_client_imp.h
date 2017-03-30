//
// Created by ganze on 17-3-30.
//

#ifndef RPLIDAR_RPC_LIDAR_CLIENT_IMP_H
#define RPLIDAR_RPC_LIDAR_CLIENT_IMP_H

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include "pb/lidar.grpc.pb.h"

class lidar_client_imp {
private:
    device::token                               m_user_token;
    std::unique_ptr<device::lidar_server::Stub> m_stub;
public:
    lidar_client_imp(
            const std::string & address,
            const std::string & device_path
    );
    device::lidar_raw_points get_points();
    bool start() ;
    bool stop() ;
};


#endif //RPLIDAR_RPC_LIDAR_CLIENT_IMP_H
