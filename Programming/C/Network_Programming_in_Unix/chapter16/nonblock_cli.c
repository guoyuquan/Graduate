#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/select.h>

#define MAXLINE 9128
#define forever for(;;)

int max(int a, int b)
{
    return a>b?a:b;
}

char *gf_time();

void str_cli(FILE *fp, int sockfd)
{
    int maxfdp1, val, stdineof;
    ssize_t n, nwritten;
    fd_set rset, wset;
    char to[MAXLINE], fr[MAXLINE];
    char *toiptr, *tooptr, *friptr, *froptr;
    if((val=fcntl(sockfd, F_GETFL, 0))<0)
    {
        fprintf(stderr, "error: fcntl(get %d): %s\n", sockfd, strerror(errno));
        return;
    }
    if(fcntl(sockfd, F_SETFL, val|O_NONBLOCK)<0)
    {
        fprintf(stderr, "error: fcntl(set %d): %s\n", sockfd, strerror(errno));
        return;
    }
    if((val=fcntl(STDIN_FILENO, F_GETFL, 0))<0)
    {
        fprintf(stderr, "error: fcntl(get %d): %s\n", STDIN_FILENO, strerror(errno));
        return;
    }
    if(fcntl(STDIN_FILENO, F_SETFL, val|O_NONBLOCK)<0)
    {
        fprintf(stderr, "error: fcntl(set %d): %s\n", STDIN_FILENO, strerror(errno));
        return;
    }
    
    toiptr=tooptr=to;
    friptr=froptr=fr;
    stdineof=0;
    
    maxfdp1=max(max(STDIN_FILENO, STDOUT_FILENO), sockfd)+1;
    
    forever
    {
        FD_ZERO(&rset);
        FD_ZERO(&wset);
        if(stdineof==0 &&toiptr<&to[MAXLINE])
            FD_SET(STDIN_FILENO, &rset); //read from stdin
        if(friptr<&fr[MAXLINE])
            FD_SET(sockfd, &rset);//read to socket
        if(tooptr!=toiptr)
            FD_SET(sockfd, &wset); //data to write to socket
        if(froptr!=friptr)
            FD_SET(STDOUT_FILENO, &wset); //data to write to stdout;
        if(select(maxfdp1, &rset, &wset, NULL, NULL)<0)
        {
            fprintf(stderr, "error: select(), %s\n", strerror(errno));
            return;
        }
        if(FD_ISSET(STDIN_FILENO, &rset))
        {
            if((n=read(STDIN_FILENO, toiptr, &to[MAXLINE]-toiptr))<0)
            {
                if(errno != EWOULDBLOCK)
                {
                    fprintf(stderr, "error: read from stdin: %s\n", strerror(errno));
                    return;
                }
            }
            else if(n==0)
            {
                fprintf(stderr, "%s: EOF on stdin\n", gf_time());
                stdineof=1;
                if(tooptr==toiptr)
                {
                    shutdown(sockfd, SHUT_WR);
                }
            }
            else
            {
                fprintf(stderr, "%s: read %zd bytes from stdin\n", gf_time(), n);
                toiptr+=n;
                FD_SET(sockfd, &wset);
            }
        }
        if(FD_ISSET(sockfd, &rset))
        {
            if((n=read(sockfd, friptr, &fr[MAXLINE]-friptr))<0)
            {
                if(errno!=EWOULDBLOCK)
                {
                    fprintf(stderr, "read error on socket");
                }
            }
            else if(n==0)
            {
                fprintf(stderr, "%s: EOF on socket\n", gf_time());
                if(stdineof)
                    return;
                else
                    fprintf(stderr, "server terminated prematurely\n");
            }
            else
            {
                fprintf(stderr, "%s: read %zd bytes from socket\n", gf_time(), n);
                friptr+=n;
                FD_SET(STDOUT_FILENO, &wset);
            }
        }
        if(FD_ISSET(STDOUT_FILENO, &wset)&&((n=friptr-froptr)>0))
        {
            if((nwritten=write(STDOUT_FILENO, froptr, n))<0)
            {
                if(errno!=EWOULDBLOCK)
                {
                    fprintf(stderr, "error: write to stdout, %s\n", strerror(errno));
                    return;
                }
            }
            else
            {
                fprintf(stderr, "%s: wrote %zd bytes to stdout\n", gf_time(), nwritten);
                froptr+=nwritten;
                if(froptr==friptr)
                    froptr=friptr=fr;//back to beginning of buffer
            }
        }
        if(FD_ISSET(sockfd, &wset)&&((n=toiptr-tooptr)>0))
        {
            if((nwritten=write(sockfd, tooptr, n))<0)
            {
                if(errno!=EWOULDBLOCK)
                {
                    fprintf(stderr, "error: write to socket: %s\n", strerror(errno));
                    return;
                }
            }
            else
            {
                fprintf(stderr, "%s: wrote %zd bytes to socket\n", gf_time(), nwritten);
                tooptr+=nwritten;
                if(tooptr==toiptr)
                {
                    toiptr=tooptr=to;
                    if(stdineof)
                        shutdown(sockfd, SHUT_WR);
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        fprintf(stderr, "usage: time <IP address>\n");
        exit(0);
    }
    int sock;
    if((sock=socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        fprintf(stderr, "error: socket() %s\n", strerror(errno));
        exit(0);
    }
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family=AF_INET;
    serv.sin_port=htons(9868);
    if(inet_pton(AF_INET, (void *)&serv.sin_addr, argv[1])<0)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(0);
    }
    if(connect(sock, (struct sockaddr *)&serv, sizeof(serv))<0)
    {
        fprintf(stderr, "error: connect to server %s : %s\n", argv[1], strerror(errno));
        exit(0);
    }
    str_cli(stdin, sock);
    exit(0);
}

char *gf_time()
{
    struct timeval tv;
    static char str[30];
    char *ptr;
    if(gettimeofday(&tv, NULL)<0)
    {
        fprintf(stderr, "gettimeof day error: %s\n", strerror(errno));
        return ptr;
    }
    ptr=ctime(&tv.tv_sec);
    strcpy(str, &ptr[11]);
    snprintf(str+8, sizeof(str)-8, ".%06d", tv.tv_usec);
    return str;
}


