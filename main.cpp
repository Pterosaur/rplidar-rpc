#include <iostream>
#include "lidar_server_imp.h"

int main() {
    RunRPCServerImp::StartRPCServer("0.0.0.0:11111");
    char ch;
    do {
        ch = getchar();
    } while(ch != 'Q' && ch != 'q');
    return 0;
}