cmake_minimum_required(VERSION 3.0)
project(lidar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(INCLUDE_DIRS
        ../../pb
        .
        thrid/RPLidarA1M1/include
        include)
set(LIBRARY_DIRS
        lib/)
set(LIBRARIES
        rplidar_sdk
        pthread
        dl
        grpc
        grpc++
        libprotobuf.a
)
set(EXECUTABLE_OUTPUT_PATH
        ../bin)
set(LIBRARY_OUTPUT_PATH
        ../lib)

include_directories(${INCLUDE_DIRS})
link_directories(${LIBRARY_DIRS})
link_libraries(${LIBRARIES})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

aux_source_directory(
        ../../pb/
        PROTOBUF_FILE)

set(PUBLIC_FILES
        imp/rplidar_a1m1.cpp
        src/lidar.cpp
        ${PROTOBUF_FILE}
        )

set(LIDAR_INTERFACE_FILES
        ${PUBLIC_FILES})
add_library(lidar_interface STATIC ${LIDAR_INTERFACE_FILES})
#target_link_libraries(lidar_interface
#        librplidar_sdk.a
#        libprotobuf.a)

set(SOURCE_FILES
        main.cpp
        ${PUBLIC_FILES})
add_executable(lidar ${SOURCE_FILES})


#target_link_libraries(lidar
#        libprotobuf.a)

