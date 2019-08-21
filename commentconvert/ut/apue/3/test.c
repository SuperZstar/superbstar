
/**********************************************************
*    > File Name: test.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月29日 星期五 19时08分49秒
**********************************************************/


#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>
#include<string.h>
#include<dirent.h>

//1 Copy Tool
//2 direction order

int main()
{
    char path[100] = {0};
    getcwd(path, 100);

    //printf("path = %s\n",path);
    
    DIR *dirp = opendir(path);

    struct dirent *ptr;
    while((ptr = readdir(dirp)) != NULL)
    {
        printf("%s ",ptr->d_name);
    }
    printf("\n");

    return 0;
}

/*
int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_WRONLY);

    //close(STDOUT_FILENO);
    //int fd1 = dup(fd);
                        //1
    int fd1 = dup2(fd, fd);

    printf("hfjaljfljljkfjalflafa\n");
    return 0;
}

/*
int main(int argc, char *argv[])
{
    int fd = creat(argv[1], 0755);
    assert(fd != -1);
    printf("fd = %d\n",fd);

    int fd1 = open(argv[1], O_RDWR);
    printf("fd1 = %d\n",fd1);

    char buf[100];
    memset(buf, 0, 100);

    char *s1 = "hello world.";
    write(fd1, s1, strlen(s1));
    
    lseek(fd1, 20, SEEK_SET); //SEEK_SET start  //SEEK_CUR cur  //SEEK_END end

    char *s2 = "hello linux.";
    write(fd1, s2, strlen(s2));

    //while(1)
    //{
    //    printf("input msg:>");
    //    scanf("%s", buf);
    //    if(strcmp(buf, "quit") == 0)
    //        break;
    //    strcat(buf,"\n");
    //    write(fd1, buf, strlen(buf));
    //}


    close(fd1);
    return 0;
}

/*
// ./test myfile.txt

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0755);
    if(fd == -1)
    {
        printf("open or creat %s fail.\n",argv[1]);
    }
    else
    {
        printf("fd = %d\n",fd);
    }

    close(fd);

    return 0;
}

/*
int main(int argc, char *argv[])
{
    int fd = creat(argv[1], 0755);
    //int fd = creat(argv[1], S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
    if(fd == -1)
    {
        printf("create %s fail\n",argv[1]);
        return -1;
    }
    else
    {
        printf("fd = %d\n",fd);
    }




    return 0;
}
*/
