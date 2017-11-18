
/**********************************************************
 *    > File Name: setval_sem.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Fri 03 Nov 2017 07:40:03 PM CST
 **********************************************************/

#include"utili.h"

int main(int argc, char *argv[])
{
    if(4 != argc)
    {
        printf("<Warning Usage>: %s pathname proj_id sem_ini_val\n", argv[0]);
        return -1;
    }

    key_t sem_key = Ftok(argv[1], atoi(argv[2]));

    int sem_id = Semget(sem_key, 0, 0);

    union semun init;
    init.val = atoi(argv[3]);
    int ret = semctl(sem_id, 0, SETVAL, init);
    if(-1 == ret)
        printf("semctl semval failure\n");
    else
        printf("semctl semval success\n");
    return 0;
}
