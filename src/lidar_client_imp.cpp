//
// Created by ganze on 17-3-30.
//

#include "lidar_client_imp.h"
#include "device/lidar.h"

lidar_client_imp::lidar_client_imp(
        const std::string &address,
        const std::string & device_path )
        : m_stub(
        device::lidar_server::NewStub(
                grpc::CreateChannel(address, grpc::InsecureChannelCredentials()))) {
    grpc::ClientContext context;
    device::connect_info info;
    info.set_path(device_path.c_str());
    grpc::Status status = m_stub->create(&context, info, &m_user_token);
    if ( ! status.ok()) {
        throw device::lidar_init_exception("cannot start" + address + " : " + device_path);
    }
}

device::lidar_raw_points lidar_client_imp::get_points() {
    grpc::ClientContext context;
    device::lidar_raw_points points;
    if ( ! m_stub->get_points(&context, m_user_token, &points).ok()) {
        throw device::lidar_runtime_exception("cannot receive data");
    }
    return points;
}

bool lidar_client_imp::start() {
    grpc::ClientContext context;
    google::protobuf::Empty e;
    return m_stub->start(&context, m_user_token, &e).ok();
}

bool lidar_client_imp::stop() {
    grpc::ClientContext context;
    google::protobuf::Empty e;
    return m_stub->stop(&context, m_user_token, &e).ok();
}
