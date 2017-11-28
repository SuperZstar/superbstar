
/**********************************************************
 *    > File Name: ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Sun 26 Nov 2017 07:48:56 PM CST
 **********************************************************/
#include"../utili.h"
#include"../uti.h"

void *thread_handler(void *arg);

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

        pthread_t tid;
        pthread_create(&tid, NULL, thread_handler, &sockConn);
    }

    close(sockSer);
    return 0;
}

void* thread_handler(void *arg)
{
    int sockConn = *(int *)arg;
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
