#ifndef _UTILI_H
#define _UTILI_H
/**********************************************************
*    > File Name: utili.h
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Fri 03 Nov 2017 07:42:05 PM CST
**********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/sem.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

key_t Ftok(const char *pathname, int proj_id)
{
    key_t sem_key = ftok(pathname, proj_id);
    if(-1 == sem_key)
    {
        perror("ftok");
        exit(1);
    }
    return sem_key;
}

int Semget(key_t key, int nsems, int semflg)
{
    int sem_id = semget(key, nsems, semflg);
    if(-1 == sem_id)
    {
        perror("semget");
        exit(1);
    }
    return sem_id;
}

/*int Semctl(int semid, int semnum, int cmd, ...)
{
    int ret = semctl(semid, semnum, cmd, ...);
    if(-1 == ret)
    {
        perror("semctl");
        exit(1);
    }
}*/

int Semop(int semid, struct sembuf *sops, unsigned nsops)
{
    int ret = semop(semid, sops, nsops);
    if(-1 == ret)
    {
        perror("semop");
        exit(1);
    }
    return ret;
}
#endif // _UTILI_H
