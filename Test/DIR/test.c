
/**********************************************************
*    > File Name: test.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Tue 17 Oct 2017 08:52:16 PM CST
**********************************************************/

#include<stdio.h>
#include<unistd.h>

int main()
{
    char path[100];
    getcwd(path, 100);
    printf("path = %s\n",path);
    chdir("/home/superbstar/Desktop/");
    getcwd(path, 100);
    printf("new path = %s\n",path);
    return 0;
}

