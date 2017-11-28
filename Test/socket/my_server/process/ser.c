
/**********************************************************
 *    > File Name: ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Mon 27 Nov 2017 04:09:31 PM CST
 **********************************************************/

#include"../utili.h"

void process_handler(int sockConn);

int main(char argc, char *argv[])
{
    int sock_fd = start_up(argv[1], atoi(argv[2]), TCP);

    struct sockaddr_in addrCli;
    socklen_t addrlen = sizeof(struct sockaddr_in);

    while(1)
    {
        int cli_fd = Accept(sock_fd, (struct sockaddr*)&addrCli, &addrlen);
        fprintf(stderr, "Accept %d Thread Success!\n", cli_fd);

        pid_t pid = fork();
        if(0 == pid)
        {
            process_handler(cli_fd);
            exit(0);
        }
        else if(pid > 0)
        {
            //int status;
            //wait(&status);
            //close(cli_fd);    //可不可以不要，毕竟在子进程中对其进行了关闭
        }
        else
        {
            perror("fork.");
            exit(1);
        }
    }

    close(sock_fd);
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
            fprintf(stderr, "%d Client Leave.\n", sockConn);
            break;
        }

        if(ADD == oper.op)
            result = oper.op1 + oper.op2;
        else if(SUB == oper.op)
            result = oper.op1 - oper.op2;
        else if(MUL == oper.op)
            result = oper.op1 * oper.op2;
        else if(DIV == oper.op)
            result = oper.op1 / oper.op2;
        else if(MOD == oper.op)
            result = oper.op1 % oper.op2;
        else if(ADD == oper.op)
            break;
        else
            fprintf(stderr, "输入指令不存在.\n");

        int sendbyte = send(sockConn, &result, sizeof(result), 0);
        if(sendbyte <= 0)
        {
            perror("send.");
            continue;
        }
    }

    close(sockConn);
}
