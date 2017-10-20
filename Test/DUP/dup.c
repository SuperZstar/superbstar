
/**********************************************************
*    > File Name: dup.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sun 15 Oct 2017 09:39:57 AM EDT
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char *argv[])
{
    int fd = open("z.txt", O_RDWR|O_CREAT, 0755);
    if(-1 == fd)
    {
        printf("asd\n");
        exit(1);
    }
    else
    {
        printf("fd = %d\n",fd);     //no '\n' will not printf;
    }
    close(STDOUT_FILENO);
    int fd1 = dup2(fd,5);
    printf("fd1 = %d\n", fd1);
    return 0;
}
