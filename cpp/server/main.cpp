#include <iostream>
#include "server.h"
//c语言中的头文件
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

//open
#include <fcntl.h>

//tcp

//测试服务
int testServer();

//测试signal
int testSignal();

//测试 sigaction
int testSigAction();

//测试fork
int testFork();

//测试 daemon
int testDaemon();

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

//测试signal  简单实现
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
//     void (*sa_handler)(int); //处理函数
//     void (*sa_sigaction)(int, siginfo_t *, void *);//处理函数
//     sigset_t sa_mask;//掩码
//     int sa_flags;//根据 SA_SIGINFO 来选择 调用  sa_handler(0) 或者 sa_sigaction(1)
//     void (*sa_restorer)(void);// 设置为NULL 一般不用
// }

// 测试 sigaction
// https://blog.csdn.net/weibo1230123/article/details/81411827
int testSigAction()
{
    // int sigaction(int sig,const struct sigaction* act, struct sigaction* oact );
    struct sigaction act, oact;
    act.sa_handler = handlerSignal;
    sigfillset(&act.sa_mask);
    act.sa_flags = 0; //使用第一个参数
    sigaction(SIGINT, &act, &oact);

    pause();

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
    int fd;
    pid_t pid; //
    if ((pid = fork()) < 0)
    {
        std::cout << "can not create suprocess!" << std::endl;
    }
    else
    {
        if (pid != 0)
        {
            exit(0);
        }
    }

    setsid(); //建立新的会话

    if (chdir("/") < 0)
    {
        std::cout << "can not change dir" << std::endl;
        exit(-1);
    }

    //把标准输入 输出 错误重定向到 /dev/null
    //man 2 open
    fd = open("dev/null", O_RDWR);
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    while (1)
    {
        sleep(1);
    }
    return 1;
}

//测试 daemon
int testDaemon()
{
    //调用 系统api 将进程切换到后台
    if (daemon(0, 0) == -1)
    {
        std::cout << "error" << std::endl;
        exit(-1);
    }
    while (1)
    {
        sleep(1);
    }
    return 1;
}

