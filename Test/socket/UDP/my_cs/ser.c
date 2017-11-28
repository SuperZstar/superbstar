
/**********************************************************
*    > File Name: ser.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sun 26 Nov 2017 12:34:55 PM CST
**********************************************************/

#include"utili.h"

int main(char argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "<Warning used>:Please input %s, IP, port.\n", argv[0]);
        return -1;
    }

    int socket_fd = Socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addrSer, addrCli;
    memset(&addrSer, 0, sizeof(struct sockaddr_in));
    addrSer.sin_family = AF_INET;
    addrSer.sin_addr.s_addr = inet_addr(argv[1]);
    addrSer.sin_port = htons(atoi(argv[2]));

    socklen_t len = sizeof(struct sockaddr_in);
    Bind(socket_fd, (struct sockaddr *)&addrSer, len);

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];

    while(1)
    {
        recvfrom(socket_fd, recvbuf, BUFFER_SIZE, 0, (struct sockaddr*)&addrCli, &len);
        fprintf(stderr, "Cli->:%s\n", recvbuf);
        fprintf(stderr, "Ser->:");
        scanf("%s", sendbuf);
        if(!strcmp(sendbuf, "quit")
                break;
        sendto(socket_fd, sendbuf, strlen(sendbuf)+1, 0, (struct sockaddr*)&addrCli, len);
    }

    close(socket_fd);
    return 0;
}
