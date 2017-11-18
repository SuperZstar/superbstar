
/**********************************************************
 *    > File Name: v_sem.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Fri 03 Nov 2017 08:34:52 PM CST
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

    struct sembuf op = {0, 1, 0};
    int ret = semop(sem_id, &op, 1);
    if(-1 == ret)
        printf("semop v_sem failure\n");
    else
        printf("semop v_sem success\n");

    return 0;
}

