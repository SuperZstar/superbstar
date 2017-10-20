
/**********************************************************
*    > File Name: fcntl.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Mon 16 Oct 2017 05:05:46 AM EDT
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<error.h>

void my_err(const char* err_string, int line)
{
    fprintf(stderr, "line:%d ", line);
    perror(err_string);
    exit(1);
}

int main()
{
    int ret;
    int access_mode;
    int fd;

    if((fd = open("a.txt", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU)) == -1)
    {
        my_err("open", __LINE__);
    }
    
    if((ret = fcntl(fd, F_SETFL, O_APPEND)) < 0)
    {
        my_err("fcntl", __LINE__);
    } 

    if((ret = fcntl(fd, F_GETFL, 0)) < 0)
    {
        my_err("fcntl", __LINE__);
    }
    access_mode = ret & O_ACCMODE;      //O_ACCMODE = 3
   // printf("%d\n", O_APPEND);           //O_APPEND = 1024
    //printf("%d\n", O_NONBLOCK);         //O_NONBLOCK = 2048
  //  printf("%d\n", O_SYNC);             //O_SYNC = 1052672
//    printf("%d\n", O_ASYNC);            //O_ASYNC = 8192
    if(access_mode == O_RDONLY)
    {
        printf("a.txt access mode: read only");
    }
    else if(access_mode == O_WRONLY)
    {
        printf("a.txt access mode: write only");
    }
    else if(access_mode == O_RDWR)
    {
        printf("a.txt access mode: read + write");
    }

    if(ret & O_APPEND)
    {
        printf(" ,append");
    }
    if(ret & O_NONBLOCK)
    {
        printf(" ,nonblock");
    }
    if(ret & O_SYNC)
    {
        printf(" ,sync");
    }
    printf("\n");

    return 0;
}
