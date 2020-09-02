#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
/**
 *  client 基本流程
 *  socket                    -> connect ->send -> recv -> close
 */

/**
 * 理论上建立socket时是指定协议:应该用PF_xxxx 设置地址时应该用AF_xxxx
 * 当然AF_INET和PF_INET的值是相同的，混用也不会有太大的问题
 */

#define PORT 8112
#define MESSAGE 1024

int main(int argc, char *argv[])
{
    int socket_fd;
    int ret = -1;
    //#include <sys/socket.h>
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1)
    {
        std::cout << "create socket failed " << std::endl;
        exit(-1);
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    //inet_addr #include <arpa/inet.h>
    //将十进制IP 转成网络字节序IP
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = connect(socket_fd, (struct sockaddr *)&server_addr,
                  sizeof(server_addr));
    if (ret == -1)
    {
        std::cout << "connect server failed" << std::endl;
        exit(-1);
    }

    std::cout << "connect success" << std::endl;

    char buffer_send[MESSAGE] = {
        0,
    };
    char buffer_recv[MESSAGE] = {
        0,
    };
    for (;;)
    {
        memset(buffer_send, 0, MESSAGE); //清空buffer_send
        std::cout << "input keys what you want send" << std::endl;
        gets(buffer_send);

        if (strcmp(buffer_send, "exit") == 0)
        {
            std::cout << "disconnect from server" << std::endl;
            break;
        }

        ret = send(socket_fd, buffer_send, MESSAGE, 0);
        if (ret == -1)
        {
            std::cout << "send data failed" << std::endl;
            break;
        }
        ret = recv(socket_fd, buffer_recv, MESSAGE, 0);
        buffer_recv[ret] = '\0';

        std::cout << "recv data is " << buffer_recv << std::endl;
    }

    //#include <unistd.h>
    close(socket_fd);

    return 1;
}