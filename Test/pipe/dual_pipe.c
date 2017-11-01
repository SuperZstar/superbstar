
/**********************************************************
 *    > File Name: dual_pipe.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Sat 28 Oct 2017 03:03:13 PM CST
 **********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

int main(void)
{
    int     pipe1[2], pipe2[2];
    pid_t   pid;
    int     stat_val;

    printf("realize full-duplex communication:\n\n");
    if(pipe(pipe1))
    {
        printf("pipe1 failed!\n");
        exit(1);
    }
    if(pipe(pipe2))
    {
        printf("pipe2 failed!\n");
        exit(1);
    }

    pid = fork();
    switch (pid)
    {   
        case -1:// {
            printf("fork error!\n");
            exit(1);//}
        case 0:
        {
        close(pipe1[1]);
        close(pipe2[0]);

        char *message1 = "from child process!\n";
        write(pipe2[1], message1, strlen(message1)+1);

        char message2[100];
        read (pipe1[0], message2, 100);
        printf("child process read from pipe:%s", message2);

        exit(0);
        }
        default:
        {
        close(pipe1[0]);
        close(pipe2[1]);

        char *message1 = "from parent process!\n";
        write (pipe1[1], message1, strlen(message1)+1);

        char message2[100];
        read(pipe2[0], message2, 100);
        printf("parent process read from pipe:%s", message2);

        wait (&stat_val);
        exit(0);
        }
    }   
    return 0;
}
