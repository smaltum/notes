/**
 * server class
 * @author sm
 * @date 2020-08-07
 * @copyleft GPL 2.0
 */
#include "server.h"
#include <iostream> //c++中的头文件 不加.h
#include <unistd.h> //c语言中的头文件 要加.h

namespace st
{

    Server::Server()
    {
        std::cout << "Server()" << std::endl;
    }

    Server::~Server()
    {
        std::cout << "~Server()" << std::endl;
    }

    void Server::run()
    {
        while (1)
        {
            std::cout << "running ... " << std::endl;
            ::usleep(1000000); //sleep 1 second
        }
    }

} // namespace st