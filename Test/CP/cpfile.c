
/**********************************************************
*    > File Name: cpfile.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sun 15 Oct 2017 04:52:33 AM EDT
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDWR, S_IRUSR|S_IWUSR|S_IXUSR|S_IRWXG);
    if(fd == -1)
    {
        printf("open %s file fatal!\n");
        exit(1);
    }
    char buf[100];

    int fd1 = creat(argv[2], 0775);
    memset(buf, 0, 100);
    while(1)
    {
        int ret = read(fd, buf, 100);
        if(ret == 0)
            break;
        write(fd1, buf, ret);
    }

    close(fd);
    close(fd1);
}
