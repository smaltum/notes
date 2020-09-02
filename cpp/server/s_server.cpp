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

// 实现参考 https://blog.csdn.net/jinmie0193/article/details/78951055

#include <iostream>
//man socket
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>

#include <arpa/inet.h>

#define PORT 8112
#define MESSAGE_LEN 1024

//开启socket server
int startServer();

int main(int argc, char *argv[])
{
    daemon(0, 0);
    return startServer();
}

//开启socket server
int startServer()
{
    //create socket
    int socket_fd;

    //#include <sys/socket.h>
    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        std::cout << "failed to create socket " << std::endl;
        exit(-1);
    }
    int ret = -1;

    //set opt of socket
    socklen_t flag = 1;
    ret = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    if (ret == -1)
    {
        std::cout << "failed to set socketopt" << std::endl;
        exit(-1);
    }

    //bind
    //netinet/in.h
    struct sockaddr_in local_addr, remote_addr;
    local_addr.sin_family = PF_INET; //IPV4 或者 IPV6
    /**
     *  PF_LOCAL        Host-internal protocols, formerly called PF_UNIX,
     *  PF_UNIX         Host-internal protocols, deprecated, use PF_LOCAL,
     *  PF_INET         Internet version 4 protocols,
     *  PF_ROUTE        Internal Routing protocol,
     *  PF_KEY          Internal key-management function,
     *  PF_INET6        Internet version 6 protocols,
     *  PF_SYSTEM       System domain,
     *  PF_NDRV         Raw access to network device
     */
    local_addr.sin_port = htons(PORT); //端口
    local_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(local_addr.sin_zero), 8);

    ret = bind(socket_fd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr_in));

    if (ret == -1)
    {
        std::cout << "failed to bind socket" << std::endl;
        exit(-1);
    }

    //listener
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
        socklen_t socklen_t = sizeof(struct sockaddr);
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
        //unistd.h
        //close
        close(accept_fd);
    }
    std::cout << "server finished " << std::endl;
    close(socket_fd);
    return 1;
}
