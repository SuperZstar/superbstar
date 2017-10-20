
/**********************************************************
*    > File Name: cp.c
*    > Author: zhangxinxin
*    > Mail: 694041531@qq.com 
*    > Created Time: Sun 15 Oct 2017 08:16:49 AM EDT
**********************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>

void version()
{
    printf("copy - v1.0\n");
}
void help()
{
    printf("This is help info file.\n");
}

#define PATH_SIZE 100



void copy_file(char *src_file, char *dest_file)
{
    FILE *src = fopen(src_file, "r");
    if(src == NULL)
    {
        printf("open %s error.\n", src_file);
        exit(1);
    }
    FILE *dest = fopen(dest_file, "w");
    if(dest == NULL)
    {
        printf("open %s error.\n", dest_file);
        exit(1);
    }

    char buffer[128];
    memset(buffer, 0, 128);
    while(!feof(src))
    {
        fgets(buffer, 128, src);
        fputs(buffer, dest);
    //    memset(buffer, 0, 128);
    }

    fclose(src);
    fclose(dest);
}

int main(int argc, char *argv[])
{
    char src_path[PATH_SIZE] = {0};
    char dest_path[PATH_SIZE] = {0};
    int option;
    while((option = getopt(argc, argv, "s:d:hv")) != -1)
    {
        switch(option)
        {
        case 's':
            strcpy(src_path, optarg);
            break;
        case 'd':
            strcpy(dest_path, optarg);
            break;
        case 'h':
            help();
            break;
        case 'v':
            version();
            break;
        case '?':
            printf("%c option invalid", optarg);
            break;
        }
    }

    copy_file(src_path, dest_path);

    return 0;
}
