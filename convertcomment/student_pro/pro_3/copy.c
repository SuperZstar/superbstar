
/**********************************************************
*    > File Name: copy.c
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年10月10日 星期二 14时56分59秒
**********************************************************/
#include<stdio.h>
#include<stdlib.h>

int copyfile(char *fileread,char *filewrite);

int main()
{
    char fileread[100];//要复制的文件名
    char filewrite[100];//要复制后的文件名

    //用户输入
    printf("要复制的文件：");
    scanf("%s",fileread);
    printf("要复制后的文件：");
    scanf("%s",filewrite);

    if(copyfile(fileread,filewrite))
    {
        printf("复制成功 \n");
    }
    else
    {
        printf("复制失败 \n");
    }

    return 0;
}

int copyfile(char *fileread,char *filewrite)
{
    FILE *fpread;//指向要复制的文件
    FILE *fpwrite;//指向复制后的文件
    int bufferlen = 1024*4;//缓冲区长度
    char *buffer = (char*)malloc(bufferlen);//开辟缓存
    int readcount;//实际读取的字节数

    if((fpread = fopen(fileread,"rb")) ==NULL || (fpwrite = fopen(filewrite,"wb")) == NULL)
    {
        printf("打开文件失败! \n");
//        getch();
        exit(1);
    }

    while((readcount = fread(buffer,1,bufferlen,fpread))>0)
    {
        fwrite(buffer,readcount,1,fpwrite);
    }

    free(buffer);
    fclose(fpread);
    fclose(fpwrite);

    return 1;

}

