#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    int sockfd;
    socklen_t len;
    struct sockaddr_in cliaddr, servaddr;
    if(argc!=2)
    {
        fprintf(stderr, "usage: ./a.out <IP address>\n");
        exit(0);
    }
    if((sockfd=socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        fprintf(stderr, "error:create socket\n");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(9868);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<0)
    {
        fprintf(stderr, "error: inet_pton\n");
        exit(0);
    }
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0)
    {
        fprintf(stderr, "error: connect\n");
        exit(0);
    }
    len=sizeof(cliaddr);
    if(getsockname(sockfd, (struct sockaddr*)&cliaddr, &len)<0)
    {
        fprintf(stderr, "error: getsockname\n");
        exit(0);
    }
    printf("local address %s\n", inet_ntoa(cliaddr.sin_addr));
    exit(0);
}