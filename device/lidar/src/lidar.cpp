//
// Created by ganze on 16-10-25.
//

#include "device/lidar.h"
#include "../imp/rplidar_a1m1.h"

namespace device {

    handle_lidar MakeLidar(LIDAR_TYPE type) {
        switch (type) {
            case LIDAR_TYPE::RPLIDARA1M1:
                return handle_lidar(new rplidar_a1m1);
            default:
                return handle_lidar();
        }

    }

    lidar::lidar() {
    }

    lidar::~lidar() {
    }
}
