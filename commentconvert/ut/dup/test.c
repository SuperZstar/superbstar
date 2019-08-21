
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月13日 星期五 18时51分16秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main()
{
    int fd = open("a.txt",O_WRONLY|O_CREAT, 0755);
    if(fd == -1)
    {
        printf("open %s error.\n","a.txt");
        exit(1);
    }

    close(STDOUT_FILENO);//close(1);
    dup(fd);
    
    printf("Hello SY.\n");
    printf("jflalkfjalkfjlkajfla\n");
    return 0;
}
