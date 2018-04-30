
/**********************************************************
*    > File Name: cli.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sun 29 Apr 2018 05:08:04 AM EDT
**********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 1024

int main()
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock_fd)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addrSer;
    socklen_t addrlen = sizeof(addrSer);
    memset(&addrSer, 0, addrlen);

    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(8080);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = connect(sock_fd, (struct sockaddr*)&addrSer, addrlen);
    if (-1 == ret)
    {
        perror("connect");
        exit(1);
    }

    char sendbuf[BUFFER_SIZE] = {0};
    char recvbuf[BUFFER_SIZE] = {0};
    while(1)
    {
        printf("[%d]Cli->:", sock_fd);
        fgets(sendbuf, 1024, stdin);
        sendbuf[strlen(sendbuf)-1] = '\0';
        if (!strncasecmp("quit", sendbuf, 4))
        {break;}
        int sendbyte = send(sock_fd, sendbuf, strlen(sendbuf)+1, 0);
        if (-1 == sendbyte)
        {
            perror("send in client");
            exit(1);
        }
        int recvbyte = recv(sock_fd, recvbuf, BUFFER_SIZE, 0);
        if (-1 == recvbyte)
        {
            perror("recv in client");
            exit(1);
        }
        printf("Ser->:%s\n", recvbuf);
    }
    close(sock_fd);
    return 0;
}
