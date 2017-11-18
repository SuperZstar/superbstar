
/**********************************************************
 *    > File Name: remove_msg.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Sun 05 Nov 2017 05:21:29 PM CST
 **********************************************************/

#include"utili.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {   
        printf("<Warning usage>:%s pathname proj_id\n", argv[0]);
        return -1;
    }   
    key_t msg_key = Ftok(argv[1], atoi(argv[2]));
    int msg_id = msgget(msg_key, 0); 
    int ret = msgctl(msg_id, IPC_RMID, NULL);
    if(-1 == ret)
        printf("remove msg failure\n");
    else
        printf("remove msg success\n");
    return 0;
}
