
/**********************************************************
 *    > File Name: client.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Sun 05 Nov 2017 03:19:55 PM CST
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
    qid = Msgget(msgkey, 0);

    while(1)
    {
        Msgrcv(qid, &msgbuffer, BUF_SIZE, SERVER_MSG, 0);
        printf("Server:%s\n", msgbuffer.ctrlstring);
        printf("Client:");
        scanf("%s", msgbuffer.ctrlstring);
        if(strncmp("quit", msgbuffer.ctrlstring, 4) == 0)
        {
            Msgctl(qid, IPC_RMID, NULL);
            break;
        }
        //msgbuffer.ctrlstring[strlen(msgbuffer.ctrlstring)] = '\0';
       
        msgbuffer.msgtype = CLIENT_MSG;
        Msgsnd(qid, &msgbuffer, strlen(msgbuffer.ctrlstring)+1, 0);
    }
    msgctl(qid, IPC_RMID, NULL);
    exit(0);
}
