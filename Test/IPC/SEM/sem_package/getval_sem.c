
/**********************************************************
 *    > File Name: getval_sem.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Fri 03 Nov 2017 08:07:28 PM CST
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

    int ret = semctl(sem_id, 0, GETVAL);
    if(-1 == ret)
        printf("semctl getval failure\n");
    else
        printf("semctl getval = %d\n", ret);

    return 0;
}
