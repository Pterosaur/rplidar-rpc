//
// Created by ganze on 16-10-25.
//

#include "rplidar_a1m1.h"
#include "3rd/spdlog/spdlog.h"
#include <iostream>

namespace device {
    using namespace rp::standalone::rplidar;
#define LIDAR_LOG_WARN(FORMAT, ARGS...) \
    LOG_WARN("DeviceLidar", FORMAT, ARGS)
#define LIDAR_LOG_ERROR(FORMAT, ARGS...) \
    LOG_ERROR("DeviceLidar", FORMAT, ARGS)




    rplidar_a1m1::rplidar_a1m1() {
        m_drv = RPlidarDriver::CreateDriver();
        if (!m_drv) {
            LIDAR_LOG_ERROR("insufficient memory.","");
            exit(-2);
        }
    }

    rplidar_a1m1::~rplidar_a1m1() {
        if (m_drv->isConnected()) {
            Stop();
        }
        RPlidarDriver::DisposeDriver(m_drv);
    }

    bool rplidar_a1m1::Init(const std::string &path) {
        m_drv->reset();
        if (IS_FAIL(m_drv->connect(path.c_str(), BAUDRATE))) {
            LIDAR_LOG_WARN(
                    "cannot bind to the specified serial port {}.",
                    path.c_str());
            return false;
        }
        else if (!GetHealthStatus()) {
            return false;
        }
        return true;
    }

    bool rplidar_a1m1::Start() {
        u_result op_result = m_drv->startMotor();
        if (IS_OK(op_result)) {
            sleep(1);
            op_result = m_drv->startScan();
            if (IS_OK(op_result)) {
                sleep(1);
                return true;
            }
        }
        LIDAR_LOG_WARN(
                "cannot start the lidar : {}.",
                CodeToString(op_result));
        return false;
    }

    bool rplidar_a1m1::Stop() {
        u_result op_result = 0;
        if (IS_OK(op_result = m_drv->stop())) {
            sleep(1);
            if (IS_OK(op_result = m_drv->stopMotor())) {
                sleep(1);
                if(IS_OK(op_result = m_drv->reset())) {
                    return true;
                }
            }
        }
        LIDAR_LOG_WARN(
                "cannot end the lidar : {}.",
                CodeToString(op_result));
        return false;
    }

    bool rplidar_a1m1::IsConnect() {
        return m_drv->isConnected();
    }

    bool rplidar_a1m1::GetHealthStatus() {
        u_result op_result;
        rplidar_response_device_health_t heathinfo;
        op_result = m_drv->getHealth(heathinfo);
        if (IS_OK(op_result)) {
            if (heathinfo.status != RPLIDAR_STATUS_ERROR) {
                return true;
            }
            LIDAR_LOG_ERROR(
                    "rplidar internal error detected, Please reboot the device to retry.",
                    "");
        } else {
            LIDAR_LOG_WARN(
                    "Error, cannot retrieve the lidar health, because {}.",
                    CodeToString(op_result)
            );
        }
        return false;
    }

    lidar_raw_points rplidar_a1m1::GetData(size_t &count) {
        typedef std::vector<_rplidar_response_measurement_node_t> measurement_nodes;
        measurement_nodes nodes(count);
        lidar_raw_points points;
        u_result op_result = m_drv->grabScanData(&nodes[0], count);
        if(IS_OK(op_result)) {
            m_drv->ascendScanData(&nodes[0], count);
            if (IS_OK(op_result)) {
            for (size_t pos = 0; pos < count; ++pos) {
                lidar_raw_point point;
                point.set_quality(nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);
                point.set_angle((nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f);
                point.set_distance(nodes[pos].distance_q2 / 4.0f);
                *points.add_points() = point;
            }
            return points;
            }
        }
        count = 0;
        LIDAR_LOG_WARN(
                "Cannot receive data : {}.",
                CodeToString(op_result));
        return points;
    }

    const char *rplidar_a1m1::CodeToString(u_result code) {
        switch (code) {
            case RESULT_INVALID_DATA:
                return "invalid data";
            case RESULT_OPERATION_FAIL:
                return "operation fail";
            case RESULT_OPERATION_TIMEOUT:
                return "operation timeout";
            case RESULT_OPERATION_STOP:
                return "operation stop";
            case RESULT_OPERATION_NOT_SUPPORT:
                return "operation not support";
            case RESULT_FORMAT_NOT_SUPPORT:
                return "format not support";
            case RESULT_INSUFFICIENT_MEMORY:
                return "insufficient memory";
        }
        return nullptr;
    }


#undef GET_LIDAR_LOG
#undef LIDAR_LOG_WARN
#undef LIDAR_LOG_ERROR
}
