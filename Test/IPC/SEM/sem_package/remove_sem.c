
/**********************************************************
 *    > File Name: remove_sem.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Fri 03 Nov 2017 07:31:20 PM CST
 **********************************************************/

#include"utili.h"

int main(int argc, char *argv[])
{
    if(3 != argc)
    {
        printf("<Warning Usage>: %s pathname proj_id\n", argv[0]);
        return -1;
    }

    key_t sem_key = Ftok(argv[1], atoi(argv[2]));

    int sem_id = Semget(sem_key, 0, 0);

    int ret = semctl(sem_id, 0, IPC_RMID);
    if(-1 == ret)
        printf("Remove sem failure\n");
    else
        printf("Remove sem success\n");
    return 0;
}
