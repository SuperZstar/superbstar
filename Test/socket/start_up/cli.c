
/**********************************************************
 *    > File Name: cli.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Thu 23 Nov 2017 12:24:08 PM CST
 **********************************************************/

#include"utili.h"

int main(char argc, char *argv[])
{
    int sockCli = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(atoi(argv[2]));
    addrSer.sin_addr.s_addr = inet_addr(argv[1]);

    socklen_t addrlen = sizeof(struct sockaddr_in);
    Connect(sockCli, (struct sockaddr*)&addrSer, addrlen);

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];

    while(1)
    {
        recv(sockCli, recvbuf, BUFFER_SIZE, 0);
        printf("Ser:->%s\n", recvbuf);
        printf("Cli:->");
        scanf("%s", sendbuf);
        if(!strcmp(sendbuf, "quit"))
            break;
        send(sockCli, sendbuf, strlen(sendbuf)+1, 0);
    }

    close(sockCli);
    return 0;
}
