
/**********************************************************
 *    > File Name: shm_ser.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Thu 02 Nov 2017 07:46:37 PM CST
 **********************************************************/

#include"utili.h"

int main(int argc, char *argv[])
{
    key_t shm_key = Ftok(argv[1], atoi(argv[2]));
    int shm_id = Shmget(shm_key, SHM_SIZE, IPC_CREAT|IPC_EXCL|0666);

    char *addr = (char*)Shmat(shm_id, NULL, 0);
    int sem_id = Semget(shm_key, 2, IPC_CREAT|IPC_EXCL|0755);

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
        Semop(sem_id, &v, 1);

        Semop(sem_id, &p, 1);
        printf("Cli:>%s\n", addr);
    }

    shmdt(addr);
    semctl(sem_id, 0, IPC_RMID);
    Shmctl(shm_id, IPC_RMID, NULL);
    }

    return 0;
}
