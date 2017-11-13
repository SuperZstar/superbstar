
/**********************************************************
*    > File Name: oncerun.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sat 21 Oct 2017 11:59:17 AM CST
**********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void run(void)
{
    printf("Fuction run is running in thread %u\n",pthread_self());
}

void * thread1(void *arg)
{
    pthread_t thid = pthread_self();
    printf("Current thread1's ID is %u\n", thid);
    pthread_once(&once, run);
    printf("thread1 ends\n");
}

void * thread2(void *arg)
{
    pthread_t thid = pthread_self();
    printf("Current thread2's ID is %u\n", thid);
    pthread_once(&once, run);
    printf("thread2 ends\n");
}

int main()
{
    pthread_t thid1, thid2;

    pthread_create(&thid1, NULL, thread1, NULL);
    pthread_create(&thid2, NULL, thread2, NULL);
    sleep(3);
    int ret = pthread_equal(thid1, thid2);
    if(ret == 0)
        printf("no equal\n");
    else
        printf("%d equal\n");
    printf("main thread exit!\n");
    exit(0);
}
