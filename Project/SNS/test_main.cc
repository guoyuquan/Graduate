#include "rp2p.h"
#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

int main()
{
    int on=1;
    std::string s;
    int sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    std::cout<<sock<<std::endl;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    struct timeval tv;
    tv.tv_sec=2;
    tv.tv_usec=0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &on, sizeof(on));
    sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(6868);
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr *)&server, sizeof(server))==-1)
    {
        std::cout<<"error: bind "<<strerror(errno)<<std::endl;
        exit(0);
    }
    socklen_t len=sizeof(server);
    getsockname(sock, (struct sockaddr *)&server, &len);
    char str[INET_ADDRSTRLEN];
    std::cout<<inet_ntop(AF_INET, (void *)&server.sin_addr.s_addr, str, INET_ADDRSTRLEN)<<std::endl;
    if(listen(sock, 5)==-1)
    {
        std::cout<<"error: listen"<<std::endl;
        exit(0);
    }
    while(true)
    {
        sockaddr_in client;
        socklen_t addrlen=sizeof(client);
        int consock=accept(sock, (struct sockaddr*)&client, &addrlen);
        if(consock==-1)
            continue;
        char buf[1500];
        memset(buf,0,1500);
        int ret=0;
        ret=recv(consock, buf+ret, 1500, 0);
        if(ret<0)
            continue;
        std::cout<<buf<<std::endl;
        std::string temp;
        proc_msg(buf, temp, consock);
    }
    return 0;
}