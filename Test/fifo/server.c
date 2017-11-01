
/**********************************************************
 *    > File Name: server.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Wed 01 Nov 2017 09:09:16 AM CST
 **********************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/wait.h>

#define FIFO_READ "readfifo"
#define FIFO_WRITE "writefifo"
#define BUF_SIZE 1024

int main(void)
{
    int wfd,rfd;
    char buf[BUF_SIZE];
    int len;
    pid_t pid;
    int staute;

    umask(0);
    if(mkfifo(FIFO_WRITE, S_IFIFO|0666))
    {
        printf("Can't create FIFO %s because %s", FIFO_WRITE, strerror(errno));
        exit(1);
    }
    umask(0);
    wfd = open(FIFO_WRITE, O_WRONLY);
    if(wfd == -1)
    {
        printf("open FIFO %s error: %s", FIFO_WRITE, strerror(errno));
        exit(1);
    }

    while((rfd = open(FIFO_READ, O_RDONLY)) == -1)
    {
        sleep(1);
    }

    pid = fork();
    while(1)
    {
        if(pid == 0)
        {
            len = read(rfd, buf, strlen(buf));
            if(len > 0)
            {
                buf[len] = '\0';
                printf("Client:%s\n", buf);
            }
        }
        else if(pid > 0)
        {
            printf("Server:");
            //fgets(buf, BUF_SIZE, stdin);
            scanf("%s", &buf);
            //buf[strlen(buf)-1] = '\0';            //为什么是-1？
            if(strncmp(buf, "quit", 4) == 0)
            {
                close(wfd);
                unlink(FIFO_WRITE);
                close(rfd);
                wait(&staute);
                exit(0);
            }
            write(wfd, buf, strlen(buf)+1);
        }
        else
        {
            perror("fork");
            exit(1);
        }
    }
}
