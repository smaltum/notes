#include <iostream>
//man socket
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>

#include <arpa/inet.h>

//fcntl
#include <fcntl.h>
//select
#include <sys/select.h>

#define PORT 8112
#define MESSAGE_LEN 1024

#define FD_SIZE 1024 //默认情况下 linux 就是1024

int startServer();

int main(int argc, char *argv[])
{
    return startServer();
}

//开启socket server
int startServer()
{
    int socket_fd;

    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        std::cout << "failed to create socket " << std::endl;
        exit(-1);
    }
    int ret = -1;

    socklen_t flag = 1;
    ret = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    if (ret == -1)
    {
        std::cout << "failed to set socketopt" << std::endl;
        exit(-1);
    }

    //将socket设置为非阻塞io
    int flag = -1;
    int max_fd = -1;
    int events = 0;
    fd_set fd_sets;
    int accept_fds[FD_SIZE]={-1};

    flag = fcntl(socket_fd, F_GETFL, 0);
    fcntl(socket_fd, F_SETFL, flag | O_NONBLOCK);

    max_fd = socket_fd;

    struct sockaddr_in local_addr, remote_addr;
    local_addr.sin_family = PF_INET; //IPV4 或者 IPV6
    local_addr.sin_port = htons(PORT); //端口
    local_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(local_addr.sin_zero), 8);

    ret = bind(socket_fd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr_in));

    if (ret == -1)
    {
        std::cout << "failed to bind socket" << std::endl;
        exit(-1);
    }

    int backlog = 10;
    ret = listen(socket_fd, backlog);
    if (ret == -1)
    {
        std::cout << "failed to listen socket" << std::endl;
        exit(-1);
    }

    //acept
    int accept_fd = -1;
    char in_buffer[MESSAGE_LEN] = {0};
    for (;;)
    {
        FD_ZERO(&fd_sets);
        FD_SET(socket_fd, &fd_sets);
        events = select(max_fd + 1, &fd_sets, NULL, NULL, NULL);
        socklen_t socklen_t = sizeof(struct sockaddr);
        //后续处理会阻塞线程
        accept_fd = accept(socket_fd, (struct sockaddr *)&remote_addr, &socklen_t);
        //inet_ntoa #include <arpa/inet.h>
        std::cout << "accept from " << inet_ntoa(remote_addr.sin_addr) << std::endl;
        //recv
        for (;;)
        {
            ret = recv(accept_fd, (void *)in_buffer, MESSAGE_LEN, 0);
            if (ret == 0)
            {
                break;
            }
            std::cout << "recv " << in_buffer << std::endl;
            send(accept_fd, (void *)in_buffer, MESSAGE_LEN, 0);
        }
        close(accept_fd);
    }
    std::cout << "server finished " << std::endl;
    close(socket_fd);
    return 1;
}
