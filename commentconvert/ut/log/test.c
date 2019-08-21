
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月10日 星期二 20时48分49秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<syslog.h>
#include<errno.h>

int main()
{
    openlog("syzy",LOG_PID|LOG_CONS,LOG_USER);
    FILE *fp = fopen("test.txt","r");
    if(fp == NULL)
    {
        syslog(LOG_ERR,"open test.txt file fail.");
        //syslog(LOG_ERR,"%m\n",errno);
        //syslog(LOG_ERR,"%d\n",errno);
        closelog();
        return -1;
    }
    fclose(fp);
    return 0;
}
