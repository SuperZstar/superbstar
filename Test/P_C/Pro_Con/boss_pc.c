
/**********************************************************
*    > File Name: boss_pc.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sat 18 Nov 2017 10:51:24 AM CST
**********************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

#define MAX_COUNT 20
#define BUFFER_SIZE 8
#define OVER -1

typedef struct
{
    int buffer[BUFFER_SIZE];
    pthread_mutex_t mutex;
    pthread_cond_t notfull;
    pthread_cond_t notempty;
    int write_pos;
    int read_pos;
}pc_st;

pc_st pc;

int init_pc(pc_st *pt, pc_st *attr)
{
    if(NULL != attr)
    {
        printf("attr is error value!\n");
        return 0;
    }

    memset(pt->buffer, 0, sizeof(pt->buffer));
    pthread_mutex_init(&pt->mutex, NULL);
    pthread_cond_init(&pt->notfull, NULL);
    pthread_cond_init(&pt->notempty, NULL);
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

void *clean_up(void *arg)
{
    pthread_mutex_t *mt = (pthread_mutex_t*)arg;
    pthread_mutex_unlock(mt);
}

void put(pc_st *pt, int key)
{
    pthread_mutex_lock(&pt->mutex);
    if((pt->write_pos+1) % BUFFER_SIZE == pt->read_pos)
    {
        pthread_cleanup_push(clean_up, &pt->mutex);
        pthread_cond_wait(&pt->notfull, &pt->mutex);
        pthread_cleanup_pop(0);
    }
    pt->buffer[pt->write_pos] = key;
    pt->write_pos = (pt->write_pos+1) % BUFFER_SIZE;
    pthread_cond_signal(&pt->notempty);
    pthread_mutex_unlock(&pt->mutex);
}

int get(pc_st *pt)
{
    int value;
    pthread_mutex_lock(&pt->mutex);
    if(pt->read_pos == pt->write_pos)
    {
        pthread_cleanup_push(clean_up, &pt->mutex);
        pthread_cond_wait(&pt->notempty, &pt->mutex);
        pthread_cleanup_pop(0);
    }
    value = pt->buffer[pt->read_pos];
    pt->read_pos = (pt->read_pos+1) % BUFFER_SIZE;
    pthread_cond_signal(&pt->notfull);
    pthread_mutex_unlock(&pt->mutex);
    return value;
}

void *producer()
{
    int i;
    for(i = 1; i <= MAX_COUNT; ++i)
    {
        put(&pc, i);
    }
    put(&pc, OVER);
}

void *consumer()
{
    int value;
    while(1)
    {
        value = get(&pc);
        if(value == OVER)
        //get(&pc);
        //if(pc.buffer[pc.read_pos] == OVER)
            break;
        printf("value = %d\n", value);
        //printf("value = %d\n", pc.buffer[pc.read_pos]);
    }
}

int main()
{
    init_pc(&pc, NULL);
    pthread_t pro_id, con_id;
    pthread_create(&pro_id, NULL, producer, NULL);
    sleep(1);           //防止出现段错误
    pthread_create(&con_id, NULL, consumer, NULL);

    pthread_join(pro_id, NULL);
    pthread_join(con_id, NULL);

    destroy_pc(&pc);
    return 0;
}
