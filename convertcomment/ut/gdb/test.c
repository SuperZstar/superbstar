
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月23日 星期六 15时26分12秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);
    int i;
    for(i=0; i<argc; ++i)
    {
        printf("argv[%d] = %s\n",i, argv[i]);
    }
    return 0;
}

/*
#ifdef WIN
void fun()
{
    printf("This is Windows.\n");
}
#else
void fun()
{
    printf("This is Linux.\n");
}
#endif

int main()
{
    fun();
    return 0;
}

/*
int Max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int a = 10;
    int b = 20;

    int *p = &a;
    printf("p size = %d\n",sizeof(p));
    int res = Max(a, b);
    return 0;
}
*/
