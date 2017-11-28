
/**********************************************************
 *    > File Name: ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Sun 26 Nov 2017 07:53:42 PM CST
 **********************************************************/

#include"../utili.h"
#include"../uti.h"

#define MAX_THREAD_NUM   5

typedef struct threadst
{
    int sockConn;
    int flag; //0 idle  1 busy
}threadst;

threadst threadpool[MAX_THREAD_NUM];

void* thread_handler(void *arg);
int main(int argc, char *argv[])
{
    int sockSer = start_up(argv[1], atoi(argv[2]), TCP);

    pthread_t tid[MAX_THREAD_NUM];
    int i;
    for(i=0; i<MAX_THREAD_NUM; ++i)
    {   
        pthread_create(&tid[i], NULL, thread_handler, &i);
        sleep(1);
        threadpool[i].sockConn = 0;
        threadpool[i].flag = 0;
    }

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
        for(i=0; i<MAX_THREAD_NUM; ++i)
        {
            if(threadpool[i].flag == 0)
            {
                threadpool[i].flag = 1;
                threadpool[i].sockConn = sockConn;
                break;
            }
        }
        if(i >= MAX_THREAD_NUM)
        {
            printf("Server Over Load.\n");
            continue;
        }
    }
    close(sockSer);
    return 0;
}

void* thread_handler(void *arg)
{
    int index = *(int *)arg;
    printf("[%d] thread is start up.\n",index);

    int result;
    opst oper;
    while(1)
    {
        if(threadpool[index].flag == 1)
        {
            printf("[%d] thread start working.....\n",index);
            int recvbyte = recv(threadpool[index].sockConn, &oper, sizeof(oper), 0);
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

            int sendbyte = send(threadpool[index].sockConn, &result, sizeof(result), 0);
            if(sendbyte <= 0)
            {
                perror("send");
                continue;
            }
        }
        else
        {
            printf("[%d] thread sleep......\n",index);
            sleep(1);
        }
    }
    close(threadpool[index].sockConn);
}
