#ifndef _LOG_H
#define _LOG_H
/**********************************************************
*    > File Name: log.h
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月11日 星期三 19时43分51秒
**********************************************************/

#include"utili.h"

void set_loglevel(int loglevel);
void sys_log(int loglevel, const char *file_name, int line_num, const char *format, ...);

#endif // _LOG_H
