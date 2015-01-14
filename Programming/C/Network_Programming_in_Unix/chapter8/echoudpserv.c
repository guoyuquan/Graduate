#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void echo(int, struct sockaddr *, socklen_t);

int
main(int argc, char *argv[])
{
    int sockfd;
    if((sockfd=socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        fprintf(stderr, "error: create socket\n");
        exit(0);
    }
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    bzero(&cliaddr, sizeof(cliaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(9868);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    /*if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 0, 0)<0)
    {
        fprintf(stderr, "error: setsockopt\n");
        exit(0);
    }
     */
    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0)
    {
        fprintf(stderr, "bind error\n");
        exit(0);
    }
    echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}

void
echo(int sock, struct sockaddr* addr, socklen_t cli)
{
    int n;
    char msg[1500];
    socklen_t len=cli;
    while(1)
    {
        if((n=recvfrom(sock, msg, 1500, 0, addr, &len))<0)
        {
            fprintf(stderr, "recvfrom error: %s\n", strerror(errno));
            continue;
        }
        if(sendto(sock, msg, n, 0, addr, len)<0)
        {
            fprintf(stderr, "sendto error: %s\n", strerror(errno));
            continue;
        }
    }
}

