//
// Created by ganze on 17-3-27.
//

#include "lidar_server_imp.h"

std::string lidar_server_imp::generator_token() const {
    return std::to_string(m_user_map.size());
}

grpc::Status lidar_server_imp::create(
    grpc::ServerContext * context,
    const device::connect_info * conn_info,
    device::token * tk) {
    std::lock_guard<std::mutex> lock(m_create_device_mutex);
    auto pos = m_lidars.find(conn_info->path());
    if(m_lidars.find(conn_info->path()) == m_lidars.end()) {
        try {
            auto conn =
                std::make_shared<lidar_server_imp::lidar_connector>(conn_info->path());
            pos = m_lidars.insert(
                pos,
                std::make_pair(
                    conn_info->path(), conn));
        } catch (device::lidar_init_exception e){
            return grpc::Status(
                grpc::StatusCode::INTERNAL, e.what());
        }
    }
    std::string token = generator_token();
    m_user_map[token] = std::make_shared<lidar_visitor>(pos->second);
    tk->set_key(token.c_str());
    return grpc::Status::OK;
}

grpc::Status lidar_server_imp::start(
    grpc::ServerContext * context,
    const device::token * tk,
    google::protobuf::Empty *) {
    if ( ! m_user_map[tk->key()]->m_conn->start()) {
        return grpc::Status(grpc::StatusCode::INTERNAL, "cannot start");
    }
    return grpc::Status::OK;
}

grpc::Status lidar_server_imp::stop(
    grpc::ServerContext * context,
    const device::token * tk,
    google::protobuf::Empty *) {
    if ( ! m_user_map[tk->key()]->m_conn->stop()) {
        return grpc::Status(grpc::StatusCode::INTERNAL, "cannot stop");
    }
    return grpc::Status::OK;
}

grpc::Status lidar_server_imp::get_points(
    grpc::ServerContext * context,
    const device::token * tk,
    device::lidar_raw_points * points) {
    *points = m_user_map[tk->key()]->m_conn->get_points();
    return grpc::Status::OK;
}

