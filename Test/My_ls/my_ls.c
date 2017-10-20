
/**********************************************************
*    > File Name: my_ls.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Fri 20 Oct 2017 08:46:20 PM CST
**********************************************************/

#include<stdio.h>
#include<stdlib.h>

void display_attribute(struct stat buf, char * name)
{

}

int main(char argc, char *argv[])
{
    int i, j, k, num;
    char path[PATH_MAX+1];
    char param[32];     //save parameter of command line 
    int flag_param = PARAM_NONE;
    struct stat buf;

    j = 0, num = 0;
    for(i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-')
        {
            for(k = 1; k < strlen(argv[i]); k++,j++)
            {
                param[j] = argv[i][k];
            }
            num++;  //save the number of "-"
        }
    }
    return 0;
}
