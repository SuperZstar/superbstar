
/**********************************************************
 *    > File Name: shm_cli.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Thu 02 Nov 2017 08:40:54 PM CST
 **********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>

#define SHM_SIZE 1024

union semun{
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

void *Shmat(int shmid, const void *shmaddr, int shmflg)
{
    void *addr = shmat(shmid, shmaddr, shmflg);
    if((void*)-1 == addr)
    {
        perror("shmat");
        exit(1);
    }
    return addr;
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("<Warning>:using %s pathname proj_id", argv[0]);
    }
    key_t shm_key = Ftok(argv[1], atoi(argv[2]));
    int shm_id = Shmget(shm_key, 0, 0);

    char *addr = (char*)Shmat(shm_id, NULL, 0);

    int sem_id = semget(shm_key, 0, 0);

    struct sembuf p = {1, -1 ,0};
    struct sembuf v = {0, 1, 0};


    while(1)
    {
        semop(sem_id, &p, 1);
        printf("Ser:>%s\n", addr);
        printf("Cli:>");
        scanf("%s", addr);
        if(!strcmp(addr, "quit"))
            break;
        semop(sem_id, &v, 1);
    }

    shmdt(addr);

    return 0;
}
