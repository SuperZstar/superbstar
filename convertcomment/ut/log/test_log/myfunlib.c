#ifndef _MYFUNLIB_H
#define _MYFUNLIB_H
/**********************************************************
*    > File Name: myfunlib.h
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月11日 星期三 21时15分10秒
**********************************************************/

#include"utili.h"

void  itoa(int x, char *ret)
{
    //char ret[20] = {0};
    char tmp[20] = {0};

    int mod;
    int i = 0;
    while(x)
    {
        mod = x % 10;
        x /= 10;
        tmp[i++] = mod + '0';
    }

    i--;
    int k = 0;
    while(i >= 0)
    {
        ret[k++] = tmp[i--];
    }
}

#endif // _MYFUNLIB_H
