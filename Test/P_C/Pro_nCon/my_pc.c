
/**********************************************************
 *    > File Name: my_pc.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Sat 18 Nov 2017 10:46:54 AM CST
 **********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

#define MAX_COUNT 20
#define BUFFER_SIZE 8
#define OVER -1
#define NUM 5

typedef struct pc_st
{
    int buffer[BUFFER_SIZE];
    pthread_mutex_t mutex;
    pthread_cond_t  notfull;
    pthread_cond_t  notempty;
    int write_pos;
    int read_pos;
}pc_st;

pc_st pc;

int init_pc(pc_st *pt, pc_st *attr)
{
    if(NULL != attr)
    {
        printf("attr is error value!\n");
        return -1;
    }

    memset(pt->buffer, 0, sizeof(pt->buffer));
    pthread_mutex_init(&pt->mutex, NULL);
    pthread_cond_init(&pt->notfull, NULL);
    pthread_cond_init(&pt->notempty, NULL);
    //pt->mutex = PTHREAD_MUTEX_INITIALIZER;
    //pt->notfull = PTHREAD_COND_INITIALIZER;
    //pt->notempty = PTHREAD_COND_INITIALIZER;
    pt->write_pos = 0;
    pt->read_pos = 0;
    return 0;
}

void destroy_pc(pc_st *pt)
{
    memset(pt->buffer, 0, sizeof(pt->buffer));
    pthread_mutex_destroy(&pt->mutex);
    pthread_cond_destroy(&pt->notfull);
    pthread_cond_destroy(&pt->notempty);
    pt->write_pos = 0;
    pt->read_pos = 0;
}

/*
void *clean_put(void *arg)
{
    pc_st *pt = (pc_st*)arg;
    pt->write_pos = 0;
//  pt->buffer[pt->write_pos] = key;
    pt->write_pos++;
    pthread_cond_signal(&pt->notempty);
    pthread_mutex_unlock(&pt->mutex);
}
*/

void put(pc_st *pt, int key)
{
    pthread_mutex_lock(&pt->mutex);
    if(pt->write_pos >= BUFFER_SIZE-1)
    {
        //pthread_cleanup_push(clean_put, pt);
        pthread_cond_wait(&pt->notfull, &pt->mutex);
        //pthread_cond_pop(0);
        pt->write_pos = 0;
    }
    pt->buffer[pt->write_pos] = key;
    pt->write_pos++;
    pthread_cond_signal(&pt->notempty);
    pthread_mutex_unlock(&pt->mutex);
}

void get(pc_st *pt)
{
    pthread_mutex_lock(&pt->mutex);
    if(pt->read_pos == pt->write_pos)
    {
        pthread_cond_wait(&pt->notempty, &pt->mutex);
        if(pt->read_pos == BUFFER_SIZE-1)
            pt->read_pos = 0;
        else
            pt->read_pos++;
    }
    pt->read_pos++;
    pthread_cond_signal(&pt->notfull);
    pthread_mutex_unlock(&pt->mutex);
}

void* producer(void *arg)
{
    int i;
    for(i = 1; i <= MAX_COUNT; ++i)
    {
        put(&pc, i);
    }
    put(&pc, OVER);
}

void* consumer(void *arg)
{
    while(1)
    {
        get(&pc);
        if(pc.buffer[pc.read_pos-1] == OVER)
            break;
        printf("value = %d\n",pc.buffer[pc.read_pos-1]);
    }
}

int main()
{
    init_pc(&pc, NULL);
    int i;
    pthread_t pro_id, con_id[NUM];
    pthread_create(&pro_id, NULL, producer, NULL);
    sleep(1);
    for(i = 0; i < NUM; ++i)
    {
        pthread_create(&con_id[i], NULL, consumer, NULL);
    }

    pthread_join(pro_id, NULL);
    for(i = 0; i < NUM; ++i)
    {
        pthread_join(con_id[i], NULL);
    }
    destroy_pc(&pc);
    return 0;
}
