
/**********************************************************
*    > File Name: sem.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Wed 01 Nov 2017 03:22:19 PM CST
**********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<sys/sem.h>

union semun
{
    int val;
    struct semid_ds *buf;
    ushort *array;
    struct seminfo *__buf;
    void *pad;
};

int main()
{
    key_t key = ftok("mysem", 0xff);
    if(-1 == key)
    {
        perror("ftok");
        exit(1);
    }
    printf("key = %x\n", key);
    int sem_id = semget(key, 1, IPC_CREAT|IPC_EXCL|0755);
    if(-1 == sem_id)
    {
        perror("semget");
        exit(1);
    }
    printf("sem id = %d\n", sem_id);

    union semun init;
    init.val = 2;
    semctl(sem_id, 0, SETVAL, init);

    int sem_val = semctl(sem_id, 0, GETVAL);
    printf("sem value = %d\n", sem_val);

    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 2;
    op.sem_flg = 0;
    semop(sem_id, &op, 1);

    sem_val = semctl(sem_id, 0, GETVAL);
    printf("sem value = %d\n", sem_val);
   
    int ret = semctl(sem_id, 0, IPC_RMID);
    if(-1 == ret)
    {
        perror("semctl");
        exit(1);
    }
    printf("Success.\n");
    return 0;
}
