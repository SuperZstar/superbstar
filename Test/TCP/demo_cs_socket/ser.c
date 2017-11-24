
/**********************************************************
 *    > File Name: ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Thu 23 Nov 2017 12:24:08 PM CST
 **********************************************************/

#include"utili.h"

int main()
{
    int sockSer = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sockSer)
    {
        perror("socket.");
        exit(1);
    }

    struct sockaddr_in addrSer, addrCli;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP); //= htonl(INADDR_ANY);
    //memset(sock.sin_zero, 0, sizeof(sock.sin_zero));

    int yes = 1;
    setsockopt(sockSer, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    socklen_t len = sizeof(struct sockaddr);
    int ret = bind(sockSer, (struct sockaddr*)&addrSer, len);
    if(ret == -1)
    {
        perror("bind.");
        exit(1);
    }

    listen(sockSer, LISTEN_QUEUE_SIZE);
    if(-1 == ret)
    {
        perror("listen.");
        exit(1);
    }

    printf("Server wait Client Connect.......\n");
    /*int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len);
      if(-1 == sockConn)
      {
      printf("Server Accept Client Connect Fail.\n");
      exit(1);
      }
      else
      {
      printf("Server Accept Client Connect Success.\n");
      printf("Client IP:>%s\n", inet_ntoa(addrCli.sin_addr));
      printf("Client Port:>%d\n", addrCli.sin_port);
      }*/
    int sockConn;

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    while(1)
    {
        sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len);
        if(-1 == sockConn)
        {
            printf("Server Accept Client Connect Fail.\n");
            exit(1);
        }
        else
        {
            printf("Server Accept Client Connect Success.\n");
            printf("Client IP:>%s\n", inet_ntoa(addrCli.sin_addr));
            printf("Client Port:>%d\n", addrCli.sin_port);
        }
        printf("Ser:>");
        scanf("%s", sendbuf);
        if(!strcmp(sendbuf, "quit"))
            break;
        send(sockConn, sendbuf, strlen(sendbuf)+1, 0);
        recv(sockConn, recvbuf, BUFFER_SIZE, 0);
        printf("Cli:>%s\n", recvbuf);
    }
    close(sockSer);
    return 0;
}
