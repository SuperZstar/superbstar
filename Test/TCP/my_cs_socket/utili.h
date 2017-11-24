#ifndef _UTILI_H
#define _UTILI_H
/**********************************************************
 *    > File Name: utili.h
 *    > Author: zhangxinxin
 *    > Mail: 694041531@qq.com 
 *    > Created Time: Tue 21 Nov 2017 08:53:45 PM CST
 **********************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
//#include<arpa/inet.h>

#define SERVER_PORT 4507
#define SERVER_IP "127.0.0.1"
#define LISTEN_QUEUE_SIZE 5         //5是什么意思？
#define BUFFER_SIZE 256

int Socket(int domain, int type, int protocol)
{
    int socket_fd = socket(domain, type, protocol);
    if(-1 == socket_fd)
    {   
        perror("socket.");
        exit(1);
    }   
    else
    {   
        fprintf(stderr, "create socket success!\n");
    }
    return socket_fd;
}

int Bind(int socket, const struct sockaddr *address, socklen_t address_len)
{
    int ret = bind(socket, address, address_len);
    if(-1 == ret)
    {
        perror("bind.");
        exit(1);
    }
    else
    {
        fprintf(stderr, "bind socket success!\n");
    }
    return 0;
}

int Listen(int socket, int backlog)
{
    int ret = listen(socket, backlog);
    if(-1 == ret)
    {
        perror("listen.");
        exit(1);
    }
    else
    {
        fprintf(stderr, "listen socket success!\n");
    }
}

int Accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len)
{
    int client_id = accept(socket, address, address_len);
    if(-1 == client_fd)
    {
        perror("accept.");
        exit(1);
    }
    else
    {
        fprintf(stderr, "accept socket success!\n");
    }
    return client_id;
}

ssize_t Send(int socket, const void *buffer, size_t length, int flags)
{
    ssize_t byte_num = send(socket, buffer, length, flags);
    if(-1 == byte_num)
    {
        perror("send.");
        exit(1);
    }
    return byte_num;
}

ssize_t Recv(int socket, void *buffer, size_t length, int flags)
{
    ssize_t byte_num = recv(socket, buffer, length, flags);
    if(-1 == byte_num)
    {
        perror("recv.");
        exit(1);
    }
    return byte_num;
}

int Connect(int socket, const struct sockaddr *address, socklen_t address_len)
{
    int ret = connect(socket, address, address_len);
    if(-1 == ret)
    {
        perror("connect.");
        exit(1);
    }
    else
    {
        fprintf(stderr, "connect socket success!\n");
    }
    return 0;
}
#endif // _UTILI_H
