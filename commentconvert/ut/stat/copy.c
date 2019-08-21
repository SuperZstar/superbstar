
/**********************************************************
*    > File Name: copy.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月13日 星期五 19时54分51秒
**********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>

void version()
{
    printf("copy - v1.0\n");
}
void help()
{
    printf("This is help info file.\n");
}

//  copy -s src -d dest

#define PATH_SIZE 100

void copy_file(char *src_file, char *dest_file)
{
    FILE *src = fopen(src_file, "r");
    if(src == NULL)
    {
        printf("open %s error.\n",src_file);
        exit(1);
    }
    FILE *dest = fopen(dest_file, "w");
    if(dest == NULL)
    {
        printf("open %s error.\n",dest_file);
        exit(1);
    }

    char buffer[128];
    memset(buffer, 0, 128);
    while(!feof(src))
    {
        fgets(buffer, 128, src);
        fputs(buffer, dest);
        memset(buffer, 0, 128);
    }

    fclose(src);
    fclose(dest);
}

void copy_dir(char *src_dir, char *dest_dir)
{
    DIR *dp = opendir(src_dir);

    mkdir(dest_dir, 0755);

    char src_pre_dir[PATH_SIZE] = {0};
    char src_cur_dir[PATH_SIZE] = {0};
    char dest_pre_dir[PATH_SIZE] = {0};
    char dest_cur_dir[PATH_SIZE] = {0};

    strcpy(src_pre_dir, src_dir);
    strcpy(src_cur_dir, src_dir);
    strcpy(dest_pre_dir, dest_dir);
    strcpy(dest_cur_dir, dest_dir);

    struct dirent *ptr;
    while((ptr = readdir(dp)) != NULL)
    {
        if(!strcmp(ptr->d_name, ".") || !strcmp(ptr->d_name, ".."))
            continue;
        
        strcat(src_cur_dir, "/"); // tt/aa
        strcat(src_cur_dir, ptr->d_name); // youtt/aa
        strcat(dest_cur_dir, "/");
        strcat(dest_cur_dir, ptr->d_name);
        
        struct stat info;
        if(stat(src_cur_dir, &info) < 0)
        {
            perror("stat");
            continue;
        }
        if(S_ISDIR(info.st_mode))
        {
            copy_dir(src_cur_dir, dest_cur_dir);
        }
        else
        {    
            copy_file(src_cur_dir, dest_cur_dir);
        }
        strcpy(src_cur_dir, src_pre_dir);
        strcpy(dest_cur_dir, dest_pre_dir);
    }
}

int main(int argc ,char *argv[])
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
            exit(0);
        case 'v':
            version();
            exit(0);
        }
    }

    struct stat info;
    stat(src_path, &info);
    if(S_ISDIR(info.st_mode))
    {
        copy_dir(src_path, dest_path);
    }
    else
    {
        copy_file(src_path, dest_path);
    }

    return 0;
}

















