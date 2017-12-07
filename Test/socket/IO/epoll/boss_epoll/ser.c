
/**********************************************************
 *    > File Name: ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Fri 01 Dec 2017 06:27:53 PM CST
 **********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>

#define MAX_NUM 5

int main()
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    //printf("ser:%d\n", sock_fd);
    if(-1 == sock_fd)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addrSer, addrCli;
    socklen_t addrlen = sizeof(struct sockaddr_in);

    memset(&addrSer, 0, addrlen);
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(8080);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = bind(sock_fd, (struct sockaddr *)&addrSer, addrlen);
    if(-1 == ret)
    {
        perror("bind");
        exit(1);
    }

    ret = listen(sock_fd, 5);
    if(-1 == ret)
    {
        perror("listen");
        exit(1);
    }
    char buffer[256];

    int epoll_fd = epoll_create(MAX_NUM+1);

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sock_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_fd, &ev);

    int i;
    struct epoll_event revent[MAX_NUM]; //MAX_NUM+1?????
    while(1)
    {
        ret = epoll_wait(epoll_fd, revent, MAX_NUM, -1);
        if(-1 == ret)
        {
            perror("epoll_wait");
            continue;
        }
        else if(0 == ret)
        {
            printf("Time Out!\n");
            continue;
        }
        else
        {
            for(i = 0; i < ret; ++i)
            {
                if(revent[i].data.fd == sock_fd && (revent[i].events & EPOLLIN))
                {
                    int sockConn = accept(sock_fd, (struct sockaddr*)&addrCli, &addrlen);
                    if(sockConn == -1)
                    {
                        perror("accept");
                        break;
                    }

                    ev.events = EPOLLIN;
                    ev.data.fd = sockConn;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockConn, &ev);
                    printf("New Client Come Baby!\n");
                }
                else if(revent[i].events & EPOLLIN)
                {
                    recv(revent[i].data.fd, buffer, 128, 0);
                    send(revent[i].data.fd, buffer, strlen(buffer)+1, 0);
                }


            }
        }
    }
    close(sock_fd);
    return 0;
}
