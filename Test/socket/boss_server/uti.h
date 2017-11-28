#ifndef _UTI_H
#define _UTI_H
/**********************************************************
 *    > File Name: uti.h
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Sun 26 Nov 2017 06:28:38 PM CST
 **********************************************************/

#include<stdio.h>
#include<unistd.h>

typedef enum {QUIT, ADD, SUB, MUL, DIV, MOD}OP_ENUM;
#define CMD_SIZE 10

typedef struct opst
{
    int op1;
    int op2;
    OP_ENUM op; 
}opst;

#endif // _UTI_H
