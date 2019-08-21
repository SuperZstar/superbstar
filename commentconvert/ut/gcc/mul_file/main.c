
/**********************************************************
*    > File Name: main.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月22日 星期五 21时03分08秒
**********************************************************/

#include<stdio.h>
#include"max.h"
#include"min.h"

int main()
{
    int a = 100;
    int b = 200;

    printf("max value = %d\n",Max(a,b));
    printf("min value = %d\n",Min(a,b));
    return 0;
}
