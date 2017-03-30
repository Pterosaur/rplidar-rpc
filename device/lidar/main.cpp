#include <iostream>
#include <iterator>
#include <3rd/spdlog/spdlog.h>
#include <fstream>
#include <device/lidar.h>

int main() {
    auto logger = spdlog::stdout_color_mt("DeviceLidar");

    auto lidar = device::MakeLidar(device::LIDAR_TYPE::RPLIDARA1M1);
    char command;
    if(!lidar->Init("/dev/ttyUSB0")) {
        goto quit;
    }


    std::cout<<"s:start     x:stop      p:print     q:quit"<<std::endl;
    while(std::cin >> command) {
        switch(command) {
            case 's':
            {
                lidar->Start();
            }
            break;
            case 'x':
            {
                lidar->Stop();
            }
            break;
            case 'p':
            {
                size_t count;
                do {
                    std::cout << "input expect count : ";
                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> count;
                } while(std::cin.fail());
                auto points = lidar->GetData(count);
                logger->info("data : \n\r {} \n\r count :  {}",points.DebugString(), count);
            }
            break;
            case 'q':
            {
                goto quit;
            }
            break;
        }
        std::cout<<"s:start     x:stop      p:print     q:quit"<<std::endl;
    }
quit:
    std::cout << "Bye!" << std::endl;
    return 0;
}