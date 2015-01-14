#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buf[1500];
    time_t ticks;
    if((listenfd=socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        fprintf(stderr, "error: socket\n");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(13);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, NULL, 0);
    if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0)
    {
        fprintf(stderr, "error: bind\n");
        exit(0);
    }
    listen(listenfd, 1);
    while(1)
    {
        connfd=accept(listenfd, (struct sockaddr *)0, NULL);
        ticks=time(NULL);
        snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
        for(int i=0; i<10; i++)
        {
        if(write(connfd, buf, strlen(buf))<strlen(buf))
            fprintf(stderr, "error: write()\n");
        }
        close(connfd);
    }
    exit(0);
}