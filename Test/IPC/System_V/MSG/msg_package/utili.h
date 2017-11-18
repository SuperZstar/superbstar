#ifndef _UTILI_H
#define _UTILI_H
/**********************************************************
*    > File Name: utili.h
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Fri 03 Nov 2017 07:42:05 PM CST
**********************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/stat.h>

#define BUF_SIZE 256
#define PROJ_ID 32
#define PATH_NAME "/tmp"
#define SERVER_MSG 1
#define CLIENT_MSG 2

key_t Ftok(const char *pathname, int proj_id)
{
    key_t msg_key = ftok(pathname, proj_id);
    if(-1 == msg_key)
    {
        perror("ftok");
        exit(1);
    }
    return msg_key;
}

int Msgget(key_t key, int msgflg)
{
    int msg_id = msgget(key, msgflg);
    if(-1 == msg_id)
    {
        perror("msgget");
        exit(1);
    }
    return msg_id;
}

int Msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg)
{
    int ret = msgsnd(msqid, msgp, msgsz, msgflg);
    if(-1 == ret)
    {
        perror("msgsnd");
        exit(1);
    }
    return ret;
}

int Msgrcv(int msqid, void *msgp, size_t msgsz, long int msgtyp, int msgflg)
{
    int ret = msgrcv(msqid, msgp, msgsz, msgtyp, msgflg);
    if(-1 == ret)
    {
        perror("msgrcv");
        exit(1);
    }
    return ret;
}

int Msgctl(int msqid, int cmd, struct msqid_ds *buf)
{
    int ret = msgctl(msqid, cmd, buf);
    if(-1 == ret)
    {
        perror("msgctl");
        exit(1);
    }
    return ret;
}

/*int Semop(int semid, struct sembuf *sops, unsigned nsops)
{
    int ret = semop(semid, sops, nsops);
    if(-1 == ret)
    {
        perror("semop");
        exit(1);
    }
    return ret;
}*/
#endif // _UTILI_H
