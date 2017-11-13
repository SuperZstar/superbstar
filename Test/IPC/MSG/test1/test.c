
/**********************************************************
*    > File Name: test.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sun 05 Nov 2017 04:41:42 PM CST
**********************************************************/

#include<stdio.h>
#include<string.h>

int main(void)
{
    char buf[5] = {0};
    printf("%s\n",buf);
    scanf("%s",buf);
    printf("%s\n", buf);
    char a[5];
    strncpy(a,buf,strlen(buf+1));
    printf("%s\n",a);
}
