#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void
proc(int sock);

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
    proc(sock[0]);
    //close(sock);
    return 0;
}

void
proc(int sock)
{
    char buf[1500];
    memset(buf, 0, 1500);
    while(fgets(buf, 1500, stdin)!=NULL)
    {
        if(write(sock, buf, strlen(buf))<0)
        {
            fprintf(stderr, "error: write()\n");
            fprintf(stderr, "%s\n", strerror(errno));
            return;
        }
        memset(buf, 0, 1500);
        int n;
        if((n=read(sock, buf, 1500))<=0)
        {
            fprintf(stderr, "error: read()\n");
            fprintf(stderr, "%s\n", strerror(errno));
            return;
        }
        printf("receive %d\n", n);
        printf("%s\n", buf);
        memset(buf, 0, 1500);
    }
}