
/**
 * server class
 * @author sm
 * @date 2020-08
 * @copyleft GPL 2.0
 */

#ifndef __SERVER_H__
#define __SERVER_H__

namespace st
{

    /**
     * 
     * 信号：就是一个中断
     * 信号处理的方式: 忽略、捕获、默认处理
     * linux下的信号： man 7 signal
     * 
     * 
     * man中文手册安装:
     * 1.安装依赖库和工具
     * 2.下载、编译、安装man中文手册
     * 3.修改配置文件
     * 4.解决乱码问题
     * 
     * 几个重要信号：
     * 1.SIGPIPE: 管道中止、当写入无人读取的管道时产生该信号，默认终止进程
     *      网络程序必须要处理 SIGPIPE 信号，否则当客户端退出后,服务器仍然向该 socket 发数据时, 则会引起 crash
     * 
     * 2.SIGCHLD: 子进程结束或停止时发送
     *      僵尸进程时一个早已死掉的进程,但在进程表中仍然占有位置
     *      在linux中当子进程结束时,他并没有被完全销毁,因为父进程还要用到它的信息
     *      父进程没有处理 SIGCHLD 信号 或 调用 wait 、waitpid 等待子进程结束 就会出现僵尸进程
     * 
     * 3.SIGALRM: 定时器信号、以秒未单位 默认终止进程
     * 
     * 4.SIGUSR1/SIGUSR2: 自定义 默认终止进程
     * 5.SIGINT: 键盘输入的退出信号
     * 6.SIGQUIT: 键盘输入的退出信号
     * 7.SIGHUP: 控制终端的挂起信号
     * 
     * 
     * 发送信号：
     * 1.硬件方式: ctrl+c ctrl+\
     * 2.软件方式: kill api
     * 3.安装信号
     *      简单方式：
     *          signal(int sig,void (func *)(int) );
     *  
     *      高级方式：
     *          int sigaction(int sig,const struct sigaction* act, struct sigaction* oact );
     * 
     */

    class Server
    {

    public:
        Server();
        ~Server();

    public:
        void run();
    };
} //namespace st
#endif