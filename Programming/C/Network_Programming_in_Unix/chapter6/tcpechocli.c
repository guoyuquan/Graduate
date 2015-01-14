#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/select.h>

void
proc(FILE *, int sock);

int
max(int, int);

int
main(int argc, char * argv[])
{
    if(argc<2)
    {
        fprintf(stderr, "usage: ./a.out <IP address>\n");
        exit(0);
    }
    int sock[5];
    for(int i=0; i<5; i++)
    {
        if((sock[i]=socket(AF_INET, SOCK_STREAM, 0))<0)
        {
            fprintf(stderr, "error: socket()\n");
            fprintf(stderr, "%s\n", strerror(errno));
            exit(0);
        }
    }
    for(int i=0; i<5; i++)
    {
        struct sockaddr_in sa;
        sa.sin_family=AF_INET;
        sa.sin_port=htons(9868);
        if(inet_pton(AF_INET, argv[1], &sa.sin_addr)<=0)
        {
            fprintf(stderr, "error: inetpton\n");
            exit(0);
        }

        if(connect(sock[i], (struct sockaddr *)&sa, sizeof(sa))<0)
        {
            fprintf(stderr, "error: connect()\n");
            fprintf(stderr, "%s\n", strerror(errno));
            exit(0);
        }
    }
    proc(stdin, sock[0]);
    //close(sock);
    return 0;
}

int
max(int a, int b)
{
    return a>b?a:b;
}
void
proc(FILE *fp, int sockfd)
{
    int maxfdp1, stdineof;
    fd_set rset;
    char rcvbuf[1500], sndbuf[1500];
    int n;
    memset(rcvbuf, 0, 1500);
    memset(sndbuf, 0, 1500);
    stdineof=0;
    while(1)
    {
        if(stdineof==0)
        {
            FD_SET(fileno(fp), &rset);
        }
        FD_SET(sockfd, &rset);
        maxfdp1=max(fileno(fp), sockfd)+1;
        if(select(maxfdp1, &rset, NULL, NULL, NULL)>0)
        {
            if(FD_ISSET(sockfd, &rset))
            {
                if(read(sockfd, rcvbuf, 1500)==0)
                {
                    if(stdineof==1)
                        return;
                    else
                    {
                        fprintf(stderr, "server terminated permanantly\n");
                        return;
                    }
                }
                fputs(rcvbuf, stdout);
            }
            if(FD_ISSET(fileno(fp), &rset))
            {
                if((n=read(fileno(fp), sndbuf, 1500))==0)
                {
                    stdineof=1;
                    shutdown(sockfd, SHUT_WR);
                    FD_CLR(fileno(fp), &rset);
                    continue;
                }
                else if(n<0)
                    fprintf(stderr, "error: read() sock\n");
                write(sockfd, sndbuf, strlen(sndbuf));
            }
        }
        return;
    }
}