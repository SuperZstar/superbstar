
/**********************************************************
 *    > File Name: ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Thu 23 Nov 2017 12:24:08 PM CST
 **********************************************************/

#include"utili.h"

int main(char argc, char *argv[])
{
    int sockSer = start_up(argv[1], atoi(argv[2]), TCP);

    struct sockaddr_in addrCli;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int sockConn = Accept(sockSer, (struct sockaddr*)&addrCli, &addrlen);
    
    //printf("Client IP:>%s\n", inet_ntoa(addrCli.sin_addr));
    //printf("Client Port:>%d\n", addrCli.sin_port);

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];

    while(1)
    {
        printf("Ser:->");
        scanf("%s", sendbuf);
        if(!strcmp(sendbuf, "quit"))
            break;
        send(sockConn, sendbuf, strlen(sendbuf)+1, 0);
        recv(sockConn, recvbuf, BUFFER_SIZE, 0);
        printf("Cli:->%s\n", recvbuf);
    }

    close(sockSer);
    return 0;
}
