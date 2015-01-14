#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int
main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[1500];
    struct sockaddr_in servaddr;
    
    if(argc!=2)
    {
        fprintf(stderr, "usage: a.out <IPaddress>\n");
        exit(0);
    }
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        fprintf(stderr, "error: create sock\n");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(13);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0)
    {
        fprintf(stderr, "error: inet_pton for %s\n", argv[1]);
        exit(0);
    }
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0)
    {
        fprintf(stderr, "connect error\n");
        exit(0);
    }
    int i=10;
    //while(i>0)
    //{
        n=read(sockfd, recvline, 1500);
        printf("received %d bytes\n", n);
        recvline[n]=0;
        if(fputs(recvline+1, stdout)==EOF)
        {
            fprintf(stderr, "error: fputs\n");
            exit(0);
        }
        //i--;
    //}
    if(n<0)
    {
        fprintf(stderr, "read error\n");
    }
    return 0;
}