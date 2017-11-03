
/**********************************************************
*    > File Name: create_sem.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Fri 03 Nov 2017 07:09:18 PM CST
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

    int sem_id = Semget(sem_key, 1, IPC_CREAT|IPC_EXCL|0755);
    if(-1 == sem_id)
        printf("semget sem failure\n");
    else
        printf("semget sem success\n");

    return 0;
}
