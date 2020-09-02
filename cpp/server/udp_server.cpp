
/**
 * 
 * udp server
 * 
 * socket -> bind -> recvfrom -> sendto -> close
 * 
 * udp client
 * 
 * socket         -> sendto   -> recvfrom -> close
 * 
 */
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8113
#define MESSAGE 1024

//测试udp服务
int testUdpServer();

int main(int argc, char *argv[])
{
    daemon(0, 0);
    return testUdpServer();
}
//测试udp服务
int testUdpServer()
{
    int socket_fd;
    //crete socket
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1)
    {
        std::cout << "upd server create failed" << std::endl;
        exit(-1);
    }

    std::cout << "upd server create success" << std::endl;

    struct sockaddr_in local_addr, remote_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(PORT);
    local_addr.sin_addr.s_addr = INADDR_ANY; //表示任意地址 一般就是 0.0.0.0

    //bind
    int ret = -1;
    ret = bind(socket_fd, (struct sockaddr *)&local_addr, sizeof(local_addr));
    if (ret == -1)
    {
        std::cout << "upd server bind failed" << std::endl;
        exit(-1);
    }

    std::cout << "upd server bind success" << std::endl;

    ssize_t len = 0;
    char buffer_recv[MESSAGE] = {
        0,
    };
    //recvfrom
    socklen_t addres_len = sizeof(sizeof(remote_addr));
    while (1)
    {
        len = recvfrom(socket_fd, buffer_recv, MESSAGE, 0, (struct sockaddr *)&remote_addr, &addres_len);
        if (len > 0)
        {
            std::cout << "recv form " << inet_ntoa(remote_addr.sin_addr) << std::endl;
            buffer_recv[len] = '\0';
            std::cout << "recv data is " << buffer_recv << std::endl;

            sendto(socket_fd, buffer_recv, MESSAGE, 0, (struct sockaddr *)&remote_addr, addres_len);
        }
    }

    //#include <unistd.h>
    close(socket_fd);

    return 1;
}