
/**********************************************************
 *    > File Name: pth_create.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Wed 08 Nov 2017 01:16:10 PM CST
 **********************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define MAX_THREAD_NUM 5

void* thread_fun(void *arg)
{
    /*int index = *(int *)arg;
    //printf("in thread id = %d\n", pthread_self());
    printf("[%d] child thread suggess\n", index);
    char buf[256];      //128 512都会报错
    memset(buf, 0, 256);
    sprintf(buf, "[%d] child thread over", index);
    pthread_exit(buf);
    /*int i;
      for(i = 0; i < 5; ++i)
      {
      if(3 == i)
      {
      char *str = "child quit\n";
      pthread_exit(str);
      }
      printf("This is child thread\n");
      }*/
    
    printf("1111111\n");
}

int main()
{
    int i;
    //printf("main pthread id = %d\n", pthread_self());
    pthread_t tid[MAX_THREAD_NUM];
    for(i = 0; i < MAX_THREAD_NUM; ++i)
    {
        pthread_create(&tid[i], NULL, thread_fun, (void *)&i);
    //    sleep(1);
    }


    for(i=0; i<10; ++i)
    {
        printf("aaaaaaaaaaaaaaaa\n");
    }


    return 0;
}
