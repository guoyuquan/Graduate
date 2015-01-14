#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int sockfd, n;
    char recvline[1500];
    struct sockaddr_in servaddr;
    struct in_addr **pptr;
    struct in_addr *inetaddrp[2];
    struct in_addr inetaddr;
    struct hostent *hp;
    struct servent *sp;
    if(argc!=3)
    {
        fprintf(stderr, "usage: ./a.out <hostname> <service>\n");
        exit(0);
    }
    if((hp=gethostbyname(argv[1]))==NULL)
    {
        if(inet_aton(argv[1], &inetaddr)==0)
        {
            fprintf(stderr, "hostname error for %s: %s", argv[1], hstrerror(h_errno));
            exit(0);
        }
        else
        {
            inetaddrp[0]=&inetaddr;
            inetaddrp[1]=NULL;
            pptr=inetaddrp;
        }
    }
    else
        pptr=(struct in_addr **)hp->h_addr_list;
    
    if((sp=getservbyname(argv[2], "tcp"))==NULL)
    {
        fprintf(stderr, "getservbyname error for %s\n", argv[2]);
        exit(0);
    }
    for(; *pptr!=NULL; pptr++)
    {
        if((sockfd=socket(AF_INET, SOCK_STREAM, 0))<0)
        {
            fprintf(stderr, "error, socket()\n");
            exit(0);
        }
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_port=sp->s_port;
        memcpy(&servaddr.sin_addr, *pptr, sizeof(struct in_addr));
        printf("trying %s\n", inet_ntoa(servaddr.sin_addr));
        if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))==0)
        {
            
            break;
        }
        fprintf(stderr, "error, connect()\n");
        close(sockfd);
        exit(0);
    }
    while((n=read(sockfd, recvline, 1500))>0)
    {
        recvline[n]=0;
        printf("%s\n", recvline);
    }
    exit(0);
}


