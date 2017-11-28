
/**********************************************************
 *    > File Name: ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Tue 28 Nov 2017 10:57:14 AM CST
 **********************************************************/

#include"../utili.h"

typedef struct
{
    int flag; //0:idle 1:busy
    int sockConn;
}threadpoolst;

threadpoolst threadpool[THREADPOOL_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t busy_cond = PTHREAD_COND_INITIALIZER;
//pthread_cond_t idle_cond = PTHREAD_COND_INITIALIZER;
pthread_t new_tid[MAX_SIZE-THREADPOOL_SIZE];
//int work_num = 0;     //工作中的线程个数

void *threadpool_handler(void *arg);

int main(char argc, char *argv[])
{
    int i;
    int sign = 0;   //创建阀值的条件 0：创建 1：释放
    int sock_fd = start_up(argv[1], atoi(argv[2]), TCP);

    struct sockaddr_in addrCli;
    socklen_t addrlen = sizeof(struct sockaddr_in);

    pthread_t tid[THREADPOOL_SIZE];
    for(i = 0; i < THREADPOOL_SIZE; ++i)
    {
        pthread_create(&tid[i], NULL, threadpool_handler, &i);
        sleep(1);
        threadpool[i].flag = 0;
        threadpool[i].sockConn = 0;
    }

    /*fprintf(stderr, "请输入要查询的客户端ID号：\n");
    scanf("%d", &i);
    if(1 == threadpoll[i].flag)
        fprintf(stderr, "[%d] Client Is Busy!\n");
    else
        fprintf(stderr, "[%d] Client Is Idle!\n");
    */          //什么时候应该查询？？？
    while(1)
    {
        int cli_fd = Accept(sock_fd, (struct sockaddr *)&addrCli, &addrlen);

        for(i = 0; i < THREADPOOL_SIZE; ++i)
        {
            if(0 == threadpool[i].flag)
            {
                threadpool[i].flag = 1;
                threadpool[i].sockConn = cli_fd;
                pthread_cond_broadcast(&busy_cond);
                /*if(1 == sign && i < THREADPOOL_SIZE)          
                {                                             
                    for(i = THREADPOOL_SIZE; i < MAX_SIZE; ++i)
                    {                                          
                        pthread_join(new_tid[i], NULL);         
                    }                                        
                    sign = 0;
                }*/     //不知道怎样释放？？？                                             

                //continue;
                break;
            }
        }

        if(i >= THREADPOOL_SIZE)
        {                                                       
            if(0 == sign)
            {
                for(i = THREADPOOL_SIZE; i < MAX_SIZE; ++i)     
                {                                               
                    pthread_create(&new_tid[i], NULL, threadpool_handler, &i);
                    sleep(1);
                    threadpool[i].flag = 0;
                    threadpool[i].sockConn = 0;
                }                                           
                sign = 1;
            }

            for(i = THREADPOOL_SIZE; i < MAX_SIZE; ++i)
            {
                if(0 == threadpool[i].flag)
                {
                    threadpool[i].flag = 1;
                    threadpool[i].sockConn = cli_fd;
                    pthread_cond_broadcast(&busy_cond);
                    break;
                }
            }

            if(i >= MAX_SIZE)
            {
                fprintf(stderr, "Server Over Load!\n");
            }
        }
    }

    for(i = 0; i < THREADPOOL_SIZE; ++i)
    {
        pthread_join(tid[i], NULL);
    }
    close(sock_fd);
    return 0;
}

void *threadpool_handler(void *arg)
{
    int index = *(int *)arg;
    int result;
    opst oper;

    fprintf(stderr, "[%d] Cliend Is Start Up.\n", index);

    while(1)
    {
        if(1 == threadpool[index].flag)
        {
            fprintf(stderr, "[%d] Cliend Start Working....\n", index);
            int recvbyte = recv(threadpool[index].sockConn, &oper, sizeof(opst), 0);
            if(recvbyte <= 0)
            {
                fprintf(stderr, "[%d] Cliend Sleep....\n", index);
                threadpool[index].flag = 0;
                threadpool[index].sockConn = 0; 
                //break;
                //pthread_cond_signal(&idle_cond);
                goto recycle;
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

            int sendbyte = send(threadpool[index].sockConn, &result, sizeof(int), 0);
            if(sendbyte <= 0)
            {
                fprintf(stderr, "Send Data Error!\n");
                //continue;
            }
        }
        else
        {
recycle :
            pthread_mutex_lock(&mutex);
            //fprintf(stderr, "[%d] Clien Sleep......\n", index);
            //sleep(1);
            pthread_cond_wait(&busy_cond, &mutex);
            pthread_mutex_unlock(&mutex);
        }
    }

    //close(threadpool[index].sockConn);
}
