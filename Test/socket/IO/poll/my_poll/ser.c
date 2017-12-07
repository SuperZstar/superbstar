
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
#include<poll.h>

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
    struct pollfd cli_fd[MAX_NUM+1];
    cli_fd[0].fd = sock_fd;
    cli_fd[0].events = POLLIN;
    int numfd = 1;
    int i;
    for(i = 1; i <= MAX_NUM; ++i)
    {
        cli_fd[i].fd = 0;
    }

    while(1)
    {
        ret = poll(cli_fd, numfd, -1);
        if(-1 == ret)
        {
            perror("poll");
            continue;
        }
        else if(0 == ret)
        {
            fprintf(stderr, "Time Out!\n");
            continue;
        }
        else
        {
            if(cli_fd[0].fd == sock_fd && (cli_fd[0].revents & POLLIN))
            {
                int sockConn = accept(sock_fd, (struct sockaddr*)&addrCli, &addrlen);
                if(-1 == sockConn)
                {
                    perror("accept");
                    continue;
                }

                for(i = 1; i < MAX_NUM+1; ++i)
                {
                    if(cli_fd[i].fd == 0)
                    {
                        cli_fd[i].fd = sockConn;
                        cli_fd[i].events = POLLIN;
                        numfd++;          //如果客户端退出，应该有max--问题
                        break;
                    }
                }
                if(i >= MAX_NUM+1)
                {
                    fprintf(stderr, "Server Is Over Load!\n");
                    continue;
                }
                else
                {
                    fprintf(stderr, "New Client Come Baby!\n");
                }
            }
            else
            {
                for(i = 1; i <= MAX_NUM; ++i)
                {
                    if(cli_fd[i].fd != 0 && (cli_fd[i].revents & POLLIN))
                    {
                        int recvbyte = recv(cli_fd[i].fd, buffer, 256, 0);
                        if(-1 == recvbyte)
                        {
                            perror("recv");
                            continue;
                        }
                        fprintf(stderr, "Cli->:%s\n", buffer);
                        int sendbyte = send(cli_fd[i].fd, buffer, strlen(buffer)+1, 0);
                        if(-1 == sendbyte)
                        {
                            perror("send");
                            continue;
                        }
                        //break;        //不应该有break，万一有多个客户端就绪，应该继续轮询
                    }
                }
            }
        }
    }
    close(sock_fd);
    return 0;
}
