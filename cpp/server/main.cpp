#include <iostream>
#include "server.h"
//c语言中的头文件
#include <signal.h>
#include <unistd.h>

//测试服务
int testServer();

//测试signal
int testSignal();

//测试 sigaction
int testSigAction();

int main(int argc, char *argv[])
{
    return testSigAction();
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

// struct sigaction {
//     void (*sa_handler)(int);
//     void (*sa_sigaction)(int, siginfo_t *, void *);
//     sigset_t sa_mask;
//     int sa_flags;
//     void (*sa_restorer)(void);
// }

// 测试 sigaction
// https://blog.csdn.net/weibo1230123/article/details/81411827
int testSigAction()
{
    // int sigaction(int sig,const struct sigaction* act, struct sigaction* oact );
    return 1;
}

//测试fork
int testFork()
{
    //fork include <unistd.h>
    //setsid include <stdlib.h>

    /**
     * fork 步骤:
     *  1.fork 一个子进程 父进程推出 子进程成为孤儿进程  被 init（ 进程号 1 ） 接管
     *  2.调用 setid 建立新的回话进程
     *  3.将当前工作目录切换到工作目录
     *  4.将标准输入 输出 出错 重定向 到 /dev/null 下
     */

    return 1;
}

//测试 daemon
int testDaemon()
{

    return 1;
}