
/**********************************************************
 *    > File Name: shm_ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Thu 02 Nov 2017 07:46:37 PM CST
 **********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>

#define SHM_SIZE 1024

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main(int argc, char *argv[])
{
    key_t shm_key = ftok(argv[1], atoi(argv[2]));
    int shm_id = shmget(shm_key, SHM_SIZE, IPC_CREAT|IPC_EXCL|0666);
    {
        if(-1 == shm_id)
        {
            perror("shmget");
            exit(1);
        }
    }

    char *addr = (char*)shmat(shm_id, NULL, 0);
    if((void*)addr == (void*)-1)
    {
        perror("shmat");
        shmctl(shm_id, IPC_RMID, NULL);
        exit(1);
    }
    int sem_id = semget(shm_key, 2, IPC_CREAT|IPC_EXCL|0755);
    union semun init;
    init.val = 0;
    semctl(sem_id, 0, SETVAL, init);
    semctl(sem_id, 1, SETVAL, init);

    struct sembuf p = {0, -1, 0};
    struct sembuf v = {1, 1, 0};

    while(1)
    {
        printf("Ser:>");
        scanf("%s", addr);
        if(!strcmp(addr, "quit"))
            break;

        semop(sem_id, &v, 1);

        semop(sem_id, &p, 1);
        printf("Cli:>%s\n", addr);
    }

    shmdt(addr);
    semctl(sem_id, 0, IPC_RMID);
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}
