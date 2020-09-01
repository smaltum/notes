/**
 * server基本流程
 *  socket  -> bind -> listen -> accept -> recv -> sned -> close
 *    
 * client 基本流程
 *  socket                    -> accept ->send -> recv -> close
 * 
 * ============
 * 
 * 重要的结构体
 * 
 * http://twobit.blog.chinaunix.net/uid-31407619-id-5755674.html
 */

// struct sockaddr_in  //netinet/in.h
// {
//     short int sin_family;        /* Address family */
//     unsigned short int sin_port; /* Port number */
//     struct in_addr sin_addr;     /* Internet address */
//     unsigned char sin_zero[8];   /* Same size as struct sockaddr */
// }; d

// struct in_addr
// {
//     unsigned long s_addr;
// };

// struct sockaddr
// {
//     sa_family_t sin_family; //地址族 IPV4 还是 IPV6
//     　　 char sa_data[14];  //14字节，包含套接字中的目标地址和端口信息
// };

#include <iostream>
//man socket
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>

#define PORT 8111
#define MESSAGE_LEN 1024

int main(int argc, char *argv)
{
    //socket
    int socket_fd;

    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        std::cout << "failed to create socket " << std::endl;
        exit(-1);
    }
    int on = 1;
    int ret = -1;
    ret = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    if (ret = -1)
    {
        std::cout << "failed to create socket" << std::endl;
        exit(-1);
    }

    //bind
    //netinet/in.h
    struct sockaddr_in localaddr, remoteaddr;
    localaddr.sin_family = PF_INET;
    localaddr.sin_port = htons(PORT);
    localaddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(localaddr.sin_zero), 8);

    ret = bind(socket_fd, (struct sockaddr *)&localaddr, sizeof(struct sockaddr_in));

    if (ret = -1)
    {
        std::cout << "failed to bind socket" << std::endl;
    }

    //listener
    int backlog = 10;
    ret = listen(socket_fd, backlog);
    if (ret = -1)
    {
        std::cout << "failed to bind socket" << std::endl;
        exit(-1);
    }

    //acept
    int accept_fd = -1;
    char in_buffer[MESSAGE_LEN] = {0};
    for (;;)
    {
        socklen_t socklen_t = sizeof(struct sockaddr);
        accept_fd = accept(socket_fd, (struct sockaddr *)&remoteaddr, &socklen_t);
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
        //unistd.h
        //close
        close(accept_fd);
    }
    std::cout << "server finished " << std::endl;
    close(socket_fd);
    return 1;
}