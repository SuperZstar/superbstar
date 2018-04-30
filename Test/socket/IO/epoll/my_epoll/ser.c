
/**********************************************************
 *    > File Name: ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Sun 29 Apr 2018 05:29:53 AM EDT
 **********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/epoll.h>

#define MAX_LISTEN  5
#define BUFFER_SIZE 1024
#define CLI_SIZE    5

void epoll_op(int epfd, int op, int fd, int mode)
{
    struct epoll_event ev;
    ev.events = mode;
    ev.data.fd = fd;
    int ret = epoll_ctl(epfd, op, fd, &ev);
    if (-1 == ret)
    {
        perror("epoll_ctl");
        exit(1);
    }
}
int main()
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock_fd)
    {
        perror("socket");
        exit(1);
    }
    else
    {printf("Server socket_fd is [%d]\n", sock_fd);}

    struct sockaddr_in addrSer, addrCli;
    socklen_t addrlen = sizeof(addrSer);
    memset(&addrSer, 0, addrlen);

    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(8080);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");

    int yes = 1;
    int length = sizeof(yes);
    int ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, length);  //This operation must push in front of bind, otherwise invaild.
    
    if (-1 == ret)
    {
        perror("setsockopt");
        exit(1);
    }
    ret = bind(sock_fd, (struct sockaddr*)&addrSer, addrlen);
    if (-1 == ret)
    {
        perror("bind");
        exit(1);
    }
    ret = listen(sock_fd, MAX_LISTEN);
    if (-1 == ret)
    {
        perror("listen");
        exit(1);
    }

    char buffer[BUFFER_SIZE] = {0};
    int epfd = epoll_create(CLI_SIZE+1);
    if (-1 == epfd)
    {
        perror("epoll_create");
        exit(1);
    }
    epoll_op(epfd, EPOLL_CTL_ADD, sock_fd, EPOLLIN);
    struct epoll_event revents[CLI_SIZE+1];
    int i;
    while(1)
    {
        ret = epoll_wait(epfd, revents, CLI_SIZE+1, -1);
        /*for (i=0; i<ret; ++i)
        {
            printf("%d -- %d\n", revents[i].data.fd, revents[i].events);
        }*/
        if (-1 == ret)
        {
            perror("epoll_wait");
            continue;
        }
        if (0 == ret)
        {
            printf("Time Out!");
            continue;
        }
        else
        {
            for (i=0; i<ret; ++i)
            {
                if (revents[i].data.fd == sock_fd)
                {
                    int cli_fd = accept(sock_fd, (struct sockaddr*)&addrCli, &addrlen);
                    if (-1 == cli_fd)
                    {
                        perror("accept");
                        continue;
                    }

                    epoll_op(epfd, EPOLL_CTL_ADD, cli_fd, EPOLLIN);
                    printf("[%d]Client Is Coming!\n", cli_fd);
                }
                else
                {
                    recv(revents[i].data.fd, buffer, BUFFER_SIZE, 0);
                    printf("[%d]Cli->:%s\n", revents[i].data.fd, buffer);
                    send(revents[i].data.fd, buffer, strlen(buffer)+1, 0);
                }
            }
        }
    }
    close(sock_fd);
    return 0;
}
