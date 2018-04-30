
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
#include<poll.h>

#define MAX_LISTEN  5
#define BUFFER_SIZE 1024
#define CLI_SIZE    5

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
    struct pollfd fds[CLI_SIZE+1];
    memset(fds, 0, sizeof(fds));
    fds[0].fd = sock_fd;
    fds[0].events = POLLIN;
    int i, num = 0;
    int max_fd = fds[0].fd;
    while(1)
    {
        ret = poll(fds, max_fd+1, -1);
        if (-1 == ret)
        {
            perror("poll");
            continue;
        }
        if (0 == ret)
        {
            printf("Time Out!\n");
            continue;
        }
        else
        {
            if (fds[0].revents&POLLIN)
            {
                int cli_fd = accept(sock_fd, (struct sockaddr*)&addrCli, &addrlen);
                if (-1 == cli_fd)
                {
                    perror("accept");
                    continue;
                }

                for (i=1; i<=CLI_SIZE; ++i)
                {
                    if (fds[i].fd == 0)
                    {
                        fds[i].fd = cli_fd;
                        fds[i].events = POLLIN;
                        ++num;
                        if (fds[i].fd > max_fd)
                        {max_fd = fds[i].fd;}
                        break;
                    }
                }

                if (i > CLI_SIZE)
                {printf("Server Is Over Loading!\n");}
                else
                {printf("[%d]Client Is Coming!\n", fds[i].fd);}
            }
            else
            {
                for (i=1; i<=CLI_SIZE; ++i)
                {
                    if (fds[i].revents&POLLIN)
                    {
                        char buffer[BUFFER_SIZE] = {0};
                        int recvbyte = recv(fds[i].fd, buffer, BUFFER_SIZE, 0);
                        if (-1 == recvbyte)
                        {
                            perror("recv");
                            continue;
                        }
                        printf("[%d]Cli->:%s\n", fds[i].fd, buffer);
                        int sendbyte = send(fds[i].fd, buffer, strlen(buffer)+1, 0);
                        if (-1 == sendbyte)
                        {
                            perror("send");
                            continue;
                        }
                    }
                }
            }
        }
    }
    close(sock_fd);
    return 0;
}
