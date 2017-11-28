
/**********************************************************
 *    > File Name: ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Sun 26 Nov 2017 07:38:35 PM CST
 **********************************************************/

#include"../utili.h"
#include"../uti.h"

void process_handler(int sockConn);

int main(int argc, char *argv[])
{
    int sockSer = start_up(argv[1], atoi(argv[2]), TCP);

    struct sockaddr_in addrCli;
    socklen_t addrlen = sizeof(struct sockaddr);
    while(1)
    {   
        int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &addrlen);
        if(sockConn == -1)
        {
            perror("accept");
            continue;
        }
        pid_t pid = fork();
        if(pid == 0)
        {
            process_handler(sockConn);
            exit(0);
        }
        else if(pid > 0)
        {
            close(sockConn);
        }
        else
        {
            perror("fork");
        }
    }

    close(sockSer);
    return 0;
}

void process_handler(int sockConn)
{
    int result;
    opst oper;
    while(1)
    {
        int recvbyte = recv(sockConn, &oper, sizeof(oper), 0);
        if(recvbyte <= 0)
        {
            printf("Client Go To.\n");
            break;
        }

        if(oper.op == ADD)
            result = oper.op1 + oper.op2;
        else if(oper.op == SUB)
            result = oper.op1 - oper.op2;
        else if(oper.op == MUL)
            result = oper.op1 * oper.op2;
        else if(oper.op == DIV)
            result = oper.op1 / oper.op2;
        else if(oper.op == MOD)
            result = oper.op1 % oper.op2;
        else if(oper.op == QUIT)
            break;

        int sendbyte = send(sockConn, &result, sizeof(result), 0);
        if(sendbyte <= 0)
        {
            perror("send");
            continue;
        }
    }
    close(sockConn);
}
