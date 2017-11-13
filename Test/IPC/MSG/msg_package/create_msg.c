
/**********************************************************
*    > File Name: create_msg.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sun 05 Nov 2017 05:12:15 PM CST
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
    int msg_id = msgget(msg_key, IPC_CREAT|IPC_EXCL|0755);
    if(-1 == msg_id)
        printf("create msg failure\n");
    else
        printf("create msg success\n");
    return 0;
}
