
/**********************************************************
 *    > File Name: shm_cli.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Thu 02 Nov 2017 08:40:54 PM CST
 **********************************************************/

#include"utili.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("<Warning>:using %s pathname proj_id", argv[0]);
    }
    key_t shm_key = Ftok(argv[1], atoi(argv[2]));
    int shm_id = Shmget(shm_key, 0, 0);

    char *addr = (char*)Shmat(shm_id, NULL, 0);

    int sem_id = Semget(shm_key, 0, 0);

    struct sembuf p = {1, -1 ,0};
    struct sembuf v = {0, 1, 0};

    while(1)
    {
        Semop(sem_id, &p, 1);
        printf("Ser:>%s\n", addr);

        printf("Cli:>");
        scanf("%s", addr);
        if(!strcmp(addr, "quit"))
            break;
        Semop(sem_id, &v, 1);
    }

    shmdt(addr);
    return 0;
}
