//
//  client.cpp
//  SocketClient
//
//  Created by TanHao on 15-3-4.
//  Copyright (c) 2015年 TanHao. All rights reserved.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <memory>
#include <unistd.h>
#include <stdio.h>

#define PORT 5001

int main(int argc, const char * argv[])
{
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("socket() failed:%d\n",errno);
        return -1;
    }
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    
    //socket需要与ip及端口绑定
    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    
    //忽略链接断开后的SIGPEPE信号,否则send会引起Crash
    optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval));
    
    if (connect(sock, (struct sockaddr*) &addr, sizeof(addr)) == -1)
    {
        printf("connect() failed:%d\n",errno);
        return -1;
    }
    
    char i = 'a';
    while (true)
    {
        sleep(2);
        
        char buffer[1] = {i};
        ssize_t sendret = send(sock, buffer, sizeof(buffer), 0);
        if (sendret == -1)
        {
            printf("socket broken!\n");
        }
        
        if (++i > 'z')
            i = 'a';
    }
    
    return 0;
}
