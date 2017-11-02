
/**********************************************************
*    > File Name: log.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月11日 星期三 19时45分50秒
**********************************************************/

#include"log.h"

#define LOG_BUFFER_SIZE 256

static int log_level = LOG_INFO;

static char* loglevels[] = 
{
    "LOG_EMERG", "LOG_ALERT","LOG_CRIT","LOG_ERR","LOG_WARNING","LOG_NOTICE","LOG_INFO","LOG_DEBUG"
};

void set_loglevel(int loglevel)
{
    log_level = loglevel;
}

//sys_log(LOG_ERR, file_name, line_num, "%s %s %s %s","open file fail.")

void sys_log(int loglevel, const char *file_name, int line_num, const char *format, ...)
{
    if(loglevel > log_level)
        return;

    time_t te;
    time(&te);
    struct tm *cur_time = localtime(&te);

    char buffer[LOG_BUFFER_SIZE];
    memset(buffer, 0, LOG_BUFFER_SIZE);
    strftime(buffer, LOG_BUFFER_SIZE-1, " [%x %X] ",cur_time);
    printf("%s",buffer);
    printf("%s %d:",file_name, line_num);
    printf("<%s> ", loglevels[loglevel - LOG_EMERG]);

    va_list arg_list;
    va_start(arg_list, format);
    memset(buffer, 0, LOG_BUFFER_SIZE);
    vsnprintf(buffer, LOG_BUFFER_SIZE-1, format, arg_list);
    printf("%s\n",buffer);
    va_end(arg_list);
    fflush(stdout);
}






