
/**********************************************************
 *    > File Name: rw_mutex.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Sat 11 Nov 2017 04:15:07 PM CST
 **********************************************************/

#include"my_pthread_rwlock.h"

#define NUM 5

my_pthread_rwlock_t rwlock;

void *thread_fun()
{
    my_pthread_rwlock_wrlock(&rwlock);
    printf("thread_fun get wrlock.\n");
    printf("thread_fun sleep....\n");
    sleep(2);
    printf("thread_fun wake up.\n");
    my_pthread_rwlock_unlock(&rwlock);
}

void *thread_fun1()
{
    my_pthread_rwlock_rdlock(&rwlock);
    printf("thread_fun1 get rdlock\n");
    my_pthread_rwlock_unlock(&rwlock);
}

void *thread_fun2()
{
    my_pthread_rwlock_wrlock(&rwlock);
    printf("thread_fun2 get wrlock\n");
    my_pthread_rwlock_unlock(&rwlock);
}

int main()
{
    pthread_t tid, tid1[NUM], tid2[NUM];
    int i;
    my_pthread_rwlock_init(&rwlock, NULL);
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
