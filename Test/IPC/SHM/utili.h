#ifndef _UTILI_H
#define _UTILI_H
/**********************************************************
 *    > File Name: utili.h
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Fri 03 Nov 2017 07:42:05 PM CST
 **********************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/stat.h>

#define SHM_SIZE 1024

union semun
{   
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

key_t Ftok(const char *pathname, int proj_id)
{
    key_t shm_key = ftok(pathname, proj_id);
    if(-1 == shm_key)
    {
        perror("ftok");
        exit(1);
    }
    return shm_key;
}

int Shmget(key_t key, size_t size, int shmflg)
{
    int shm_id = shmget(key, size, shmflg);
    if(-1 == shm_id)
    {
        perror("shmget");
        exit(1);
    }
    return shm_id;
}

int Shmctl(int shmid, int cmd, struct shmid_ds *buf)
{
    int ret = shmctl(shmid, cmd, buf);
    if(-1 == ret)
    {
        perror("shmctl");
        exit(1);
    }
    return ret;
}

void *Shmat(int shmid, const void *shmaddr, int shmflg)
{
    void *addr = shmat(shmid, shmaddr, shmflg);
    if((void*)-1 == addr)
    {   
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        exit(1);
    }   
    return addr;
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
