
/**********************************************************
 *    > File Name: chdir.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Mon 16 Oct 2017 08:17:11 PM CST
 **********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdlib.h>
#include<errno.h>

void my_err(const char *err_string, int line)
{
    fprintf(stderr, "line:%d ",line);
    perror(err_string);
    exit(1);
}

int main(int argc, char *argv[])
{
    char buf[PATH_MAX + 1];         //PATH_MAX not definition?

    if(argc < 2)
    {
        printf("chdir <target path>\n");
        exit(1);
    }
    if(chdir(argv[1]) < 0)
    {
        my_err("child", __LINE__);
    }
    if(getcwd(buf, 512) < 0)
    {
        my_err("getcwd", __LINE__);
    }

    printf("%s\n", buf);

    return 0;
}
