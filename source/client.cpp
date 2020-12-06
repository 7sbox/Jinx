//
//  client.cpp
//  SocketClient
//
//  Created by TanHao on 15-3-4.
//  Copyright (c) 2015年 TanHao. All rights reserved.
//

#include <errno.h>
#include <memory>
#include <stdio.h>

#ifdef _WIN32
#include <WinSock.h>
#endif
#ifdef OS_Linux
#endif
#ifdef OS_Darwin
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

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
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));
    
#ifdef SO_NOSIGPIPE
    //忽略链接断开后的SIGPEPE信号,否则send会引起Crash
    optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_NOSIGPIPE, (const char*)&optval, sizeof(optval));
#endif

    if (connect(sock, (struct sockaddr*) &addr, sizeof(addr)) == -1)
    {
        printf("connect() failed:%d\n",errno);
        return -1;
    }
    
    char i = 'a';
    while (true)
    {
        Sleep(2);
        
        char buffer[1] = {i};
        int sendret = send(sock, buffer, sizeof(buffer), 0);
        if (sendret == -1)
        {
            printf("socket broken!\n");
        }
        
        if (++i > 'z')
            i = 'a';
    }
    
    return 0;
}
