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

int main(int argc, char *argv[])
{

    int socket_fd;
    socket_fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1)
    {
        std::cout << "udp create failed" << std::endl;
        exit(-1);
    }
    std::cout << "udp create success" << std::endl;

    ssize_t len = -1;
    char buffer_send[MESSAGE] = {
        0,
    };
    char buffer_recv[MESSAGE] = {0};

    //netinet/in.h
    struct sockaddr_in remote_addr;
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(PORT);
    remote_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1)
    {
        memset(buffer_send, 0, MESSAGE);
        gets(buffer_send);

        if (!strcmp(buffer_send, "exit"))
        {
            std::cout << "exit upd send queue" << std::endl;
            break;
        }
        len = sendto(socket_fd, buffer_send, MESSAGE, 0, (struct sockaddr *)&remote_addr, sizeof(remote_addr));
        if (len > 0)
        {
            // #include <atlstr.h>
            std::cout << "upd server ip is " << std::endl;
        }
        socklen_t r_len = sizeof(remote_addr);
        len = recvfrom(socket_fd, buffer_recv, MESSAGE, 0, (struct sockaddr *)&remote_addr, &r_len);
        if (len > 0)
        {
            buffer_recv[len] = '\0';
            std::cout << "recv data is " << buffer_recv << std::endl;
        }
    }

    close(socket_fd);

    return 1;
}