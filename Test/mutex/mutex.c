
/**********************************************************
*    > File Name: mutex.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sat 11 Nov 2017 01:35:51 PM CST
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1()
{
    pthread_mutex_trylock(&mutex);
    printf("This is child pthread1\n");
    pthread_cond_wait(&cond, &mutex);
    //sleep(3);
    printf("pthread1 wake up\n");
    //char *buf = "qwer df";
    //pthread_exit(buf);
    pthread_mutex_unlock(&mutex);
}

void *thread2()
{
    pthread_mutex_lock(&mutex);
    printf("This is child pthread2\n");
    pthread_cond_wait(&cond, &mutex);
    //sleep(2);
    printf("pthread2 wake up\n");
    pthread_mutex_lock(&mutex);
}

int main()
{
    pthread_t tid1, tid2, tid[5];
    //void *retval;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid1, NULL, thread1, NULL);
    sleep(1);
    pthread_create(&tid2, NULL, thread2, NULL);
    sleep(6);
    //pthread_join(tid1, &retval);
    //printf("%s\n", retval);
    pthread_cond_broadcast(&cond);
    sleep(2);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
