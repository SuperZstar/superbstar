
/**********************************************************
 *    > File Name: cli.c
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Mon 27 Nov 2017 12:52:57 PM CST
 **********************************************************/

#include"utili.h"

int main(char argc, char*argv[])
{
    int sock_fd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addrSer;
    memset(&addrSer, 0, sizeof(addrSer));
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(atoi(argv[2]));
    addrSer.sin_addr.s_addr = inet_addr(argv[1]);

    socklen_t addrlen = sizeof(struct sockaddr_in);
    Connect(sock_fd, (struct sockaddr*)&addrSer, addrlen);

    while(1)
    {
        int result;
        //char cmd;
        int cmd;
        opst oper;
input:
        printf("****************************\n");
        printf("*           Server         *\n");
        printf("****************************\n");
        printf("*1.ADD          2.SUB      *\n");
        printf("*3.MUL          4.DIV      *\n");
        printf("*5.MOD          6.QUIT     *\n");
        printf("****************************\n");
        printf("input cmd:>");
        //scanf("%c", &cmd);
        scanf("%d", &cmd);
        //printf("%d\n", strlen(stdin));     //找一个判断输入缓冲区的方法

        //switch(cmd-48)
        switch(cmd)
        {
            case 1:
                oper.op = ADD;
                break;
            case 2:
                oper.op = SUB;
                break;
            case 3:
                oper.op = MUL;
                break;
            case 4:
                oper.op = DIV;
                break;
            case 5:
                oper.op = MOD;
                break;
            case 6:
                fprintf(stderr, "欢迎下次使用.\n");
                goto over;
                break;
            default :
                fprintf(stderr, "输入指令有误,请重新输入！\n");
                goto input;
        }

        fprintf(stderr, "input op1 & op2:>");
        scanf("%d %d", &oper.op1, &oper.op2);
        fflush(stdin);
        int sendbyte = send(sock_fd, &oper, sizeof(oper), 0);
        if(sendbyte <= 0)
        {
            fprintf(stderr, "send data error.\n");
            continue;
        }

        int recvbyte = recv(sock_fd, &result, sizeof(result), 0);
        if(recvbyte <= 0)
        {
            fprintf(stderr, "recv data error.\n");
            continue;
            //是否应该转到recv上部，而不是continue？
        }
        fprintf(stderr, "result = %d\n", result);
    }

over:
    close(sock_fd);
    return 0;
}
