//
// Created by ganze on 16-10-25.
//

#ifndef LIDAR_RPLIDARA1M1_H
#define LIDAR_RPLIDARA1M1_H

#include "device/lidar.h"
#include "../thrid/RPLidarA1M1/include/rplidar.h"
#include <exception>

namespace device {

    class rplidar_a1m1 : public lidar {
    public:
        rplidar_a1m1();

        virtual ~rplidar_a1m1();

        virtual bool Init(const std::string &path);

        virtual bool Start();

        virtual bool Stop();

        virtual bool IsConnect();

        virtual bool GetHealthStatus();

        virtual lidar_raw_points GetData(size_t &count);

    private:
        typedef rp::standalone::rplidar::RPlidarDriver rplidar_driver;
        enum {
            BAUDRATE = 115200,
        };

        const char *CodeToString(u_result code);

        rplidar_driver *m_drv;
    };

}

#endif //LIDAR_RPLIDARA1M1_H
