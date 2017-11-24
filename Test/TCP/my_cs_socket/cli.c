
/**********************************************************
*    > File Name: cli.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Fri 24 Nov 2017 08:07:23 PM CST
**********************************************************/

#include"utili.h"

int main()
{
    int sockCli = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addrSer;
    memset(&addrSer, 0, sizeof(addrSer));
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);

    Connect(sockCli, (struct sockaddr *)&addrSer, sizeof(addrSer));

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];

    while(1)
    {
        Recv(sockCli, recvbuf, BUFFER_SIZE, 0);
        fprintf(stderr, "Ser:>%s\n", recvbuf);
        fprintf(stderr, "Cli:>");
        scanf("%s", sendbuf);
        if(!strcmp(sendbuf, "quit"))
            break;
        send(sockCli, sendbuf, strlen(sendbuf)+1, 0);
    }

    close(sockCli);
    return 0;
}
