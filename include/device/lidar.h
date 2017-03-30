//
// Created by ganze on 16-10-25.
//

#ifndef LIDAR_LIDAR_H
#define LIDAR_LIDAR_H

#include <memory>
#include <string>
#include <vector>
#include "lidar.pb.h"

namespace device {

    class lidar {
    protected:
        lidar();

        virtual ~lidar();

    public:

        virtual bool Init(const std::string &path) = 0;

        virtual bool Start() = 0;

        virtual bool Stop() = 0;

        virtual bool IsConnect() = 0;

        virtual bool GetHealthStatus() = 0;

        virtual lidar_raw_points GetData(size_t &count) = 0;

    };

    struct lidar_init_exception :
            public std::runtime_error {
        lidar_init_exception(const std::string &message) :
                std::runtime_error(message) {}
        lidar_init_exception(const char *message) :
                std::runtime_error(message) {}
    };

    struct lidar_runtime_exception :
            public std::runtime_error {
        lidar_runtime_exception(const std::string & message) :
                std::runtime_error(message) {}
        lidar_runtime_exception(const char * message) :
                std::runtime_error(message) {}
    };

    typedef std::shared_ptr<lidar> handle_lidar;

    enum class LIDAR_TYPE {
        RPLIDARA1M1,
    };

    handle_lidar MakeLidar(LIDAR_TYPE);
}

#endif //LIDAR_LIDAR_H
