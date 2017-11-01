
/**********************************************************
*    > File Name: pipe.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sat 28 Oct 2017 02:08:27 PM CST
**********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

int main(void)
{
    int     fd[2];
    pid_t   pid;
    int     stat_val;

    if(pipe(fd))
    {
        printf("create pipe failed!\n");
        exit(1);
    }

    pid = fork();
    switch (pid)
    {
        case -1:
            printf("fork error!\n");
            exit(1);
        case 0:{
            close(fd[1]);
            char message[100];
            read(fd[0], message, 100);
            printf("read from pipe:%s",message);
            exit(0);
               }
        default:
            close(fd[0]);
            char *message = "Hello,pipe!\n";
            write(fd[1], message, strlen(message)+1);
            wait(&stat_val);
            exit(0);
    }
    return 0;
}
