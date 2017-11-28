
/**********************************************************
*    > File Name: ser.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Tue 21 Nov 2017 08:50:43 PM CST
**********************************************************/

#include"utili.h"

int main()
{
    int sockSer = Socket(AF_INET, SOCK_STREAM, 0);
    struct in_addr IP;

    struct sockaddr_in addrSer, addrCli;
    memset(&addrSer, 0, sizeof(struct sockaddr_in));
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);
    //addrSer.sin_addr.s_addr = htonl(IN_ADDR_ANY);
    //addrSer.sin_addr.s_addr = inet_aton(SERVER_IP, &IP);
    //printf("%x\n", IP.s_addr);

    Bind(sockSer, (struct sockaddr *)&addrSer, sizeof(addrSer));
    Listen(sockSer, LISTEN_QUEUE_SIZE);

    printf("Server wait Client Connect.......\n");
    int len = sizeof(addrSer);
    int cli_fd = Accept(sockSer, (struct sockaddr *)&addrCli, &len);

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];

    while(1)
    {
        fprintf(stderr, "Ser:>");
        scanf("%s", sendbuf);
        if(!strcmp(sendbuf, "quit"))
            break;
        Send(cli_fd, sendbuf, strlen(sendbuf)+1, 0);
        Recv(cli_fd, recvbuf, BUFFER_SIZE, 0);
        fprintf(stderr, "Cli:>%s\n", recvbuf);
    }

    close(sockSer);
    return 0;
}
