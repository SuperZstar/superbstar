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
#include<arpa/inet.h>

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

ssize_t Sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
{
    ssize_t byte_num = sendto(socket, buffer, length, flags, dest_addr, addrlen);
    if(-1 == byte_num)
    {
        perror("sendto.");
        exit(1);
    }
    return byte_num;
}

ssize_t Recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
    ssize_t byte_num = recvfrom(socket, buffer, length, flags, src_addr, addrlen);
    if(-1 == byte_num)
    {
        perror("recvfrom.");
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
