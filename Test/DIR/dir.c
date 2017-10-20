
/**********************************************************
*    > File Name: dir.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Mon 16 Oct 2017 07:22:56 PM CST
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdlib.h>
#include<errno.h>

int my_readdir(const char *path)
{
    DIR *dir;
    struct dirent *ptr;

    if((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return -1;
    }
    while((ptr = readdir(dir)) != NULL)
    {
        printf("file name: %s\n", ptr->d_name);
    }
    closedir(dir);

    return 0;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("listfile <target path>\n");
        exit(1);
    }

    if(my_readdir(argv[1]) < 0)
    {
        exit(1);
    }

    return 0;
}
