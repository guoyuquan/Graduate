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
    int listenfd, connfd, sockfd;
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
    int maxfd=listenfd;
    int maxi=-1;
    int nready, client[FD_SETSIZE];
    for(int i=0; i<FD_SETSIZE; i++)
        client[i]=-1;
    fd_set rset, allset;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    char buf[1500];
    memset(buf, 0, 1500);
    int n=0, i=0;
    while(1)
    {
        rset=allset;
        nready=select(maxfd+1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(listenfd, &rset)){
            connfd=accept(listenfd, (struct sockaddr *)&cliaddr, &len);
            //int i=0;
            for(; i<FD_SETSIZE; i++)
                if(client[i]<0)
                {
                    client[i]=connfd;
                    break;
                }
            if(i==FD_SETSIZE)
            {
                fprintf(stderr, "error: too many clients\n");
                continue;
            }
            FD_SET(connfd, &allset);
            if(connfd> maxfd)
                maxfd=connfd;
            if(i>maxi)
                maxi=i;
            if(--nready<=0)
                continue;
        }
        for(i=0; i<maxi; i++)
        {
            if((sockfd=client[i])<0)
                continue;
            if(FD_ISSET(sockfd, &rset))
            {
                if((n=read(sockfd, buf, 1500))==0)
                {
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i]=-1;
                }
                else
                    write(sockfd, buf, n);
                if(--nready<=0)
                    break;
            }
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
    else
        return;
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
