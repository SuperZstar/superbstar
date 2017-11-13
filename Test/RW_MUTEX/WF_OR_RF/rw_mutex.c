
/**********************************************************
*    > File Name: rw_mutex.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sat 11 Nov 2017 04:15:07 PM CST
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define NUM 5

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void *thread_fun()
{
    pthread_rwlock_wrlock(&rwlock);
    printf("thread_fun get wrlock.\n");
    printf("thread_fun sleep....\n");
    sleep(2);
    printf("thread_fun wake up.\n");
    pthread_rwlock_unlock(&rwlock);
}

void *thread_fun1()
{
    pthread_rwlock_rdlock(&rwlock);
    printf("thread_fun1 get rdlock\n");
    pthread_rwlock_unlock(&rwlock);
}

void *thread_fun2()
{
    pthread_rwlock_wrlock(&rwlock);
    printf("thread_fun2 get wrlock\n");
    pthread_rwlock_unlock(&rwlock);
}

int main()
{
    pthread_t tid, tid1[NUM], tid2[NUM];
    int i;
    //pthread_rwlock_init(&rwlock, NULL);
    pthread_create(&tid, NULL, thread_fun, NULL);
    sleep(1);
    for(i = 0; i < NUM; ++i)
    {
        pthread_create(&tid1[i], NULL, thread_fun1, NULL);
    }
    for(i = 0; i < NUM; ++i)
    {
        pthread_create(&tid2[i], NULL, thread_fun2, NULL);
    }

    pthread_join(tid, NULL);
    for(i = 0; i < NUM; ++i)
    {
        pthread_join(tid1[i], NULL);
    }
    for(i = 0; i < NUM; ++i)
    {
        pthread_join(tid2[i], NULL);
    }

    return 0;
}
