
/**********************************************************
*    > File Name: cli.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Fri 01 Dec 2017 06:42:10 PM CST
**********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sock_fd)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addrSer;
    socklen_t addrlen = sizeof(struct sockaddr_in);

    memset(&addrSer, 0, addrlen);
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(8080);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = connect(sock_fd, (struct sockaddr *)&addrSer, addrlen);
    if(-1 == ret)
    {
        perror("connect");
        exit(1);
    }

    char sendbuf[256];
    char recvbuf[256];

    while(1)
    {
        fprintf(stderr, "Cli->:");
        scanf("%s", sendbuf);
        if(!strcmp(sendbuf, "quit"))
            break;
        send(sock_fd, sendbuf, strlen(sendbuf)+1, 0);
        recv(sock_fd, recvbuf, 256, 0);
        fprintf(stderr, "Ser->:%s\n", recvbuf);
    }

    close(sock_fd);

    return 0;
}
