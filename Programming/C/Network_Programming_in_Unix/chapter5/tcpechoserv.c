#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

void
proc(int sock);

void
sig_chld(int signo);

int
main()
{
    int listenfd, connfd;
    if((listenfd=socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        fprintf(stderr, "error: socket()\n");
        exit(0);
    }
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(9868);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0)
    {
        fprintf(stderr, "error: bind()\n");
        exit(0);
    }
    if(listen(listenfd, 5)<0)
    {
        fprintf(stderr, "error: listen()\n");
        exit(0);
    }
    if(signal(SIGCHLD, sig_chld)==SIG_ERR)
    {
        fprintf(stderr, "error: signal()\n");
        exit(0);
    }
    struct sockaddr_in cliaddr;
    socklen_t len=sizeof(struct sockaddr_in);
    pid_t pid;
    while(1)
    {
        connfd=accept(listenfd, (struct sockaddr*)&cliaddr, &len);
        if(connfd<0)
        {
            if(errno==EINTR)
                continue;
            fprintf(stderr, "error: accept()\n");
        }
        if((pid=fork())<0)
        {
            fprintf(stderr, "error: fork()\n");
        }
        if(pid==0)
        {
            if(close(listenfd)<0)
            {
                fprintf(stderr, "error: close listen socket\n");
            }
            proc(connfd);
            if(close(connfd)<0)
            {
                fprintf(stderr, "error: close child socket\n");
                fprintf(stderr, "%s\n", strerror(errno));
            }
            exit(0);
        }
        if(close(connfd)<0)
        {
            fprintf(stderr, "%s\n", strerror(errno));
        }
    }
    return 0;
}

void
proc(int sock)
{
    char *buf=(char *)malloc(1500*sizeof(char));
    if(buf==NULL)
    {
        fprintf(stderr, "error: molloc\n");
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }
    memset(buf, 0, 1500);
    int ret=0;
again:
    while((ret=read(sock, buf, 1500))>0)
    {
        printf("received %d bytes \n %s\n", ret, buf);
        write(sock, buf, strlen(buf));
        memset(buf, 0, 1500);
    }
    if(ret<0&&errno==EINTR)
        goto again;
    else if(ret<0)
    {
        fprintf(stderr, "error: read socket: %d\n", sock);
        fprintf(stderr, "%s\n", strerror(errno));
    }
}

void
sig_chld(int signo)
{
    pid_t pid;
    int stat;
    
    while((pid=waitpid(-1, &stat, WNOHANG))>0)
    {
        printf("chiald %d terminated\n", pid);
    }
    //printf("child %d terminated\n", pid);
    return ;
}
