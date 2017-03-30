cmake_minimum_required(VERSION 3.0)
project(rplidar_rpc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIBRARY_DIRS
        lib/)

link_libraries(
        pthread
        protobuf
        grpc
        grpc++
        dl
        rplidar_sdk
)

include_directories(
        .
        include/
        pb/
)

link_directories(${LIBRARY_DIRS})
aux_source_directory(pb/ PROTOBUF_FILE)

set(SERVER_SOURCE_FILES
        main.cpp
        device/lidar/imp/rplidar_a1m1.cpp
        device/lidar/src/lidar.cpp
        ${PROTOBUF_FILE}
        src/lidar_server_imp.cpp
        )
add_executable(rplidar_rpc ${SERVER_SOURCE_FILES})

set(CLIENT_SOURCE_FILES
        ${PROTOBUF_FILE}
        src/lidar_client_imp.cpp
        include/lidar_client_imp.h)

add_library(lidar_client STATIC ${CLIENT_SOURCE_FILES})
