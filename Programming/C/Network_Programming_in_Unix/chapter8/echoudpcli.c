#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

void
echo(FILE *, int, struct sockaddr *, socklen_t);

int
main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in addr;
    if(argc!=2)
    {
        fprintf(stderr, "usage: ./a.out <IP Address>\n");
        exit(0);
    }
    bzero(&addr, sizeof(addr));
    addr.sin_len=16;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(9868);
    if(inet_pton(AF_INET, argv[1], (void *)&addr.sin_addr)<0)
    {
        fprintf(stderr, "error: inet_pton: %s\n", strerror(errno));
        exit(0);
    }
    if((sockfd=socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        fprintf(stderr, "error: create socket %s\n", strerror(errno));
        exit(0);
    }
    echo(stdin, sockfd, (struct sockaddr *)&addr, sizeof(addr));
    return 0;
}

void
echo(FILE * fp, int sock, struct sockaddr *addr, socklen_t size)
{
    int n;
    char msg[1500];
    char buf[16];
    socklen_t len=size;
    struct sockaddr_in raddr;
    bzero(&raddr, sizeof raddr);
    while((n=read(fileno(fp), msg, 1500))>0)
    {
        if(sendto(sock, msg, n, 0, addr, size)<0)
        {
            fprintf(stderr, "error: sendto %s\n", strerror(errno));
            continue;
        }
        if(recvfrom(sock, msg, 1500, 0, (struct sockaddr *)&raddr, &len)<0)
        {
            fprintf(stderr, "error: recv %s\n", strerror(errno));
            continue;
        }
        if(len!=size||memcmp(addr, &raddr, len) !=0)
        {
            printf("reply from %s (ignored)\n", inet_ntoa(raddr.sin_addr));
            continue;
        }
        //printf("******\n");
        printf("%s", msg);
    }
}