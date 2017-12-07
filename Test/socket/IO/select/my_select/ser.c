
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
#include<sys/select.h>

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
    fd_set set;
    int cli_fd[MAX_NUM] = {0};
    int cli_num = 0;
    int max = sock_fd;
    int i;

    while(1)
    {
        FD_ZERO(&set);
        FD_SET(sock_fd, &set);
        for(i = 0; i < MAX_NUM; ++i)
        {
            if(cli_fd[i] != 0)
            {
                FD_SET(cli_fd[i], &set);
            }
        }

        int ret = select(max+1, &set, NULL, NULL, NULL);
        if(-1 == ret)
        {
            perror("select");
            continue;
        }
        else if(0 == ret)
        {
            fprintf(stderr, "Time out!\n");
            continue;
        }
        else
        {
            if(FD_ISSET(sock_fd, &set))
            {
                int sockConn = accept(sock_fd, (struct sockaddr*)&addrCli, &addrlen);
                if(-1 == sockConn)
                {
                    perror("accept");
                    continue;
                }

                for(i = 0; i < MAX_NUM; ++i)
                {
                    if(cli_fd[i] == 0)
                    {
                        cli_fd[i] = sockConn;
                        cli_num++;
                        if(cli_fd[i] > max)
                            max = cli_fd[i];
                        break;
                    }
                }
                if(i >= MAX_NUM)
                    fprintf(stderr, "Server Is Over Load!\n");
                else
                    fprintf(stderr, "New Client Come Baby!\n");
            }
            else
            {
                for(i = 0; i < MAX_NUM; ++i)
                {
                    if(cli_fd[i] != 0 && FD_ISSET(cli_fd[i], &set))
                    {
                        int recvbyte = recv(cli_fd[i], buffer, 256, 0);
                        if(-1 == recvbyte)
                        {
                            perror("recv");
                            continue;
                        }
                        fprintf(stderr, "from cli->:%s\n", buffer);
                        int sendbyte = send(cli_fd[i], buffer, strlen(buffer)+1, 0);
                        if(-1 == sendbyte)
                        {
                            perror("send");
                            continue;
                        }
                        break;
                    }
                }
            }
        }
    }
    close(sock_fd);
    return 0;
}
