
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
#include<sys/select.h>

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

    int ret = bind(sock_fd, (struct sockaddr*)&addrSer, addrlen);
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
    fd_set set;
    int cli_num[CLI_SIZE] = {0};
    int i, num = 0;
    int max_num = sock_fd;
    while(1)
    {
        FD_ZERO(&set);
        FD_SET(sock_fd, &set);
        for (i=0; i<CLI_SIZE; ++i)
        {
            if (cli_num[i] != 0)
            {FD_SET(cli_num[i], &set);}
        }

        ret = select(max_num+1, &set, NULL, NULL, NULL);
        if (-1 == ret)
        {
            perror("select");
            continue;
        }
        if (0 == ret)
        {
            printf("Time Out!");
            continue;
        }
        else
        {
            if (FD_ISSET(sock_fd, &set))
            {
                int cli_fd = accept(sock_fd, (struct sockaddr*)&addrCli, &addrlen);
                if (-1 == cli_fd)
                {
                    perror("accept");
                    continue;
                }
                if (cli_fd > max_num)
                {max_num = cli_fd;}

                for (i=0; i<CLI_SIZE; ++i)
                {
                    if (cli_num[i] == 0)
                    {
                        cli_num[i] = cli_fd;
                        ++num;
                        break;
                    }
                }
                if (i == CLI_SIZE)
                {printf("Server Is OverLoad!!!\n");}
                else
                {printf("[%d]Client Is Comming!\n", cli_fd);}
            }
            else
            {
                for (i=0; i<CLI_SIZE; ++i)
                {
                    if (cli_num[i] != 0 && FD_ISSET(cli_num[i], &set))
                    {
                        int recvbyte = recv(cli_num[i], buffer, BUFFER_SIZE, 0);
                        if (-1 == recvbyte)
                        {
                            perror("recv");
                            continue;
                        }
                        printf("[%d]Cli->:%s\n", cli_num[i], buffer);
                        int sendbyte = send(cli_num[i], buffer, strlen(buffer)+1, 0);
                        if (-1 == sendbyte)
                        {
                            perror("send");
                            continue;
                        }
                        //break;
                    }
                }
            }
        }
    }
    close(sock_fd);
    return 0;
}
