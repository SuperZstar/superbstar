
/**********************************************************
 *    > File Name: ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Tue 28 Nov 2017 09:45:14 AM CST
 **********************************************************/


void *thread_handler(void *arg);

int main(char argc, char *argv[])
{
    int sock_fd = start_up(argv[1], atoi(argv[2]), TCP);

    struct sockaddr_in addrCli;
    socklen_t addrlen = sizeof(struct sockaddr_in);

    while(1)
    {
        int cli_fd = Accept(sock_fd, (struct sockaddr*)&addrCli, &addrlen);
        fprintf(stderr, "Accept %d Thread Success!\n", cli_fd);

        pthread_t tid;
        pthread_create(&tid, NULL, thread_handler, &cli_fd);

    }

    //pthread_join(tid, NULL);
    close(sock_fd);
    return 0;
}

void *thread_handler(void *arg)
{
    int cli_fd = *(int *)arg;
    int result;
    opst oper;

    while(1)
    {
        int recvbyte = recv(cli_fd, &oper, sizeof(opst), 0);
        if(recvbyte <= 0)
        {
            fprintf(stderr, "%d Client Leave.\n", cli_fd);
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

        int sendbyte = send(cli_fd, &result, sizeof(int), 0);
        if(sendbyte <= 0)
        {
            fprintf(stderr, "Send Data Error!\n");
            //continue;
        }
    }
    close(cli_fd);
}
