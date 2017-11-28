
/**********************************************************
 *    > File Name: cli.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Fri 24 Nov 2017 08:07:23 PM CST
 **********************************************************/

#include"utili.h"
#include"uti.h"

int main(int argc, char *argv[])
{
    int sockCli = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addrSer;
    memset(&addrSer, 0, sizeof(addrSer));
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(atoi(argv[2]));
    addrSer.sin_addr.s_addr = inet_addr(argv[1]);

    socklen_t addrlen = sizeof(struct sockaddr_in);
    Connect(sockCli, (struct sockaddr*)&addrSer, addrlen);

    int result;
    char cmd[BUFFER_SIZE];
    opst oper;

    while(1)
    {
        printf("****************************\n");
        printf("*           Server         *\n");
        printf("* add :>  op1 + op2        *\n");
        printf("* sub :>  op1 - op2        *\n");
        printf("****************************\n");
        printf("input cmd:>");
        scanf("%s", cmd);

        if(strcmp(cmd,"add") == 0)
            oper.op = ADD;
        else if(strcmp(cmd,"sub") == 0)
            oper.op = SUB;
        else if(strcmp(cmd,"mul") == 0)
            oper.op = MUL;
        else if(strcmp(cmd,"div") == 0)
            oper.op = DIV;
        else if(strcmp(cmd,"mod") == 0)
            oper.op = MOD;
        else if(strcmp(cmd,"quit") == 0)
            oper.op = QUIT;

        printf("input op1 and op2:>");
        scanf("%d %d", &oper.op1, &oper.op2);
        int sendbyte = send(sockCli, &oper, sizeof(oper), 0);
        if(sendbyte <= 0)
        {
            printf("send data error.\n");
            continue;
        }
        int recvbyte = recv(sockCli, &result, sizeof(result), 0);
        if(recvbyte <= 0)
        {
            printf("recv data error.\n");
            continue;
        }
        printf("result = %d\n", result);
    }

    close(sockCli);
    return 0;
}
