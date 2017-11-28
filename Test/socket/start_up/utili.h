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

#define LISTEN_Q 5         //5是什么意思？
#define BUFFER_SIZE 256

enum{TCP, UDP};

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

int Accept(int socket, struct sockaddr * address, socklen_t * address_len)
{
    int client_id = accept(socket, address, address_len);
    if(-1 == client_id)
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

int start_up(const char *ip, short port, int mode)
{
    int sockfd;
    if(TCP == mode)
        sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    else
        sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(port);
    addrSer.sin_addr.s_addr = inet_addr(ip);

    int yes = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    socklen_t addrlen = sizeof(struct sockaddr);
    Bind(sockfd, (struct sockaddr*)&addrSer, addrlen);

    if(TCP == mode)
    {
        Listen(sockfd, LISTEN_Q);
    }

    return sockfd;
}
#endif // _UTILI_H
