#ifndef _MY_PTHREAD_RWLOCK_H
#define _MY_PTHREAD_RWLOCK_H
/**********************************************************
 *    > File Name: my_pthread_rwlock.h
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Sun 12 Nov 2017 08:40:00 PM CST
 **********************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct{
    pthread_mutex_t rw_mutex;
    pthread_cond_t rw_condreaders;
    pthread_cond_t rw_condwriters;
    int rw_magic;
    int rw_nwaitreaders;
    int rw_nwaitwriters;
    int rw_refcount;
}my_pthread_rwlock_t;

enum{
    EINVAL,
    EBUSY
};

#define RW_MAGIC 0x20171112
#define MY_PTHREAD_RWLOCK_INITIALIZER {PTHREAD_MUTEX_INITIALIZER,\
    PTHREAD_COND_INITIALIZER,\
    PTHREAD_COND_INITIALIZER,\
    RW_MAGIC, 0, 0, 0}

int my_pthread_rwlock_init(my_pthread_rwlock_t *, pthread_rwlockattr_t *);
int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *);
int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *);
int my_pthread_rwlock_tryrdlock(my_pthread_rwlock_t *);
int my_pthread_rwlock_trywrlock(my_pthread_rwlock_t *);
int my_pthread_rwlock_unlock(my_pthread_rwlock_t *);
int my_pthread_rwlock_destroy(my_pthread_rwlock_t *);

int my_pthread_rwlock_init(my_pthread_rwlock_t *rw, pthread_rwlockattr_t *attr)
{
    int result;

    if(NULL != attr)
        return EINVAL;
    if(0 != (result = pthread_mutex_init(&rw->rw_mutex, NULL)))
        goto err1;
    if(0 != (result = pthread_cond_init(&rw->rw_condreaders, NULL)))
        goto err2;
    if(0 != (result = pthread_cond_init(&rw->rw_condwriters, NULL)))
        goto err3;

    rw->rw_nwaitreaders = 0;
    rw->rw_nwaitwriters = 0;
    rw->rw_refcount = 0;
    rw->rw_magic = RW_MAGIC;

    return 0;

err3:
    pthread_cond_destroy(&rw->rw_condreaders);
err2:
    pthread_mutex_destroy(&rw->rw_mutex);
err1:
    return result;
}

int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *rw)
{
    int result;

    if(RW_MAGIC != rw->rw_magic)
        return EINVAL;
    if(0 != (result = pthread_mutex_lock(&rw->rw_mutex)))
        return result;

    while(-1 == rw->rw_refcount)
    {
        rw->rw_nwaitreaders++;
        result = pthread_cond_wait(&rw->rw_condreaders, &rw->rw_mutex);
        rw->rw_nwaitreaders--;
        if(0 != result)
            break;
    }
    if(0 == result)
        rw->rw_refcount++;
    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}

int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *rw)
{
    int result;

    if(RW_MAGIC != rw->rw_magic)
        return EINVAL;
    if(0 != (result = pthread_mutex_lock(&rw->rw_mutex)))
        return result;

    while(0 != rw->rw_refcount || rw->rw_nwaitreaders > 0)
    {
        rw->rw_nwaitwriters++;
        result = pthread_cond_wait(&rw->rw_condwriters, &rw->rw_mutex);
        rw->rw_nwaitwriters--;
        if(0 != result)
            break;
    }
    if(0 == result)
        rw->rw_refcount = -1;
    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}

int my_pthread_rwlock_tryrdlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_trywrlock(my_pthread_rwlock_t *rw);

int my_pthread_rwlock_unlock(my_pthread_rwlock_t *rw)
{
    int result;

    if(rw->rw_refcount > 0)
        rw->rw_refcount--;
    else if(-1 == rw->rw_refcount)
        rw->rw_refcount = 0;
    else
        //err_dump("rw_refcount = %d", rw->rw_refcount);
        printf("rw_refcount = %d", rw->rw_refcount);

    if(rw->rw_nwaitreaders > 0)
        result = pthread_cond_broadcast(&rw->rw_condreaders);
    else if(rw->rw_nwaitwriters > 0)
    {
        if(0 == rw->rw_refcount)
            result = pthread_cond_signal(&rw->rw_condwriters);
    }

    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}

int my_pthread_rwlock_destroy(my_pthread_rwlock_t *rw)
{
    if(RW_MAGIC != rw->rw_magic)
        return EINVAL;
    if(0 != rw->rw_refcount || 0 != rw->rw_nwaitreaders || 0 != rw->rw_nwaitwriters)
        return EBUSY;

    pthread_mutex_destroy(&rw->rw_mutex);
    pthread_cond_destroy(&rw->rw_condreaders);
    pthread_cond_destroy(&rw->rw_condwriters);
    rw->rw_magic = 0;

    return 0;
}
#endif // _MY_PTHREAD_RWLOCK_H
