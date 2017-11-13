
/**********************************************************
*    > File Name: server.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sun 05 Nov 2017 01:44:35 PM CST
**********************************************************/

#include"utili.h"

int main(void)
{
    struct mymsgbuf
    {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    }msgbuffer;

    int qid;
    key_t msgkey;

    msgkey = Ftok(PATH_NAME, PROJ_ID);
    qid = Msgget(msgkey, IPC_CREAT|0660);

    while(1)
    {
        printf("Server:");
        scanf("%s", msgbuffer.ctrlstring);
        if(strncmp("quit", msgbuffer.ctrlstring, 4) == 0)
        {
            Msgctl(qid, IPC_RMID, NULL);
            break;
        }
        //msgbuffer.ctrlstring[strlen(msgbuffer.ctrlstring)] = '\0';
        msgbuffer.msgtype = SERVER_MSG;
        Msgsnd(qid, &msgbuffer, strlen(msgbuffer.ctrlstring)+1, 0);
       
        Msgrcv(qid, &msgbuffer, BUF_SIZE, CLIENT_MSG, 0);
        printf("Client:%s\n", msgbuffer.ctrlstring);
    }
    msgctl(qid, IPC_RMID, NULL);
    exit(0);
}
