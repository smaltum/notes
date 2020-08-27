#include <iostream>
#include "server.h"
//c语言中的头文件
#include <signal.h>
#include <unistd.h>

//测试服务
int testServer();

//测试signal
int testSignal();

int main(int argc, char *argv[])
{
    return testSignal();
}

//测试服务
int testServer()
{
    st::Server *server = new st::Server();
    if (server)
    {
        server->run();
    }
    return 1;
}

void handlerSignal(int sig)
{
    std::cout << "handlerSignal "
              << sig
              << std::endl;
}

//测试signal
int testSignal()
{
    //unistd.h
    //signal
    signal(SIGINT, handlerSignal);
    signal(SIGQUIT, handlerSignal);
    signal(SIGHUP, handlerSignal);

    pause();

    return 1;
}