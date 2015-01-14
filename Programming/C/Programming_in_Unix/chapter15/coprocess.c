#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 1024

static void sig_pipe(int);

int
main()
{
    int n, fd1[2], fd2[2];
    pid_t pid;
    char line[MAXLINE];
    
    if(signal(SIGPIPE, sig_pipe)==SIG_ERR)
    {
        fprintf(stderr, "error: signal()\n");
        exit(0);
    }
    
    if(pipe(fd1)<0||pipe(fd2)<0)
    {
        fprintf(stderr, "error: pipe\n");
        exit(0);
    }
    
    if((pid=fork())<0)
    {
        fprintf(stderr, "error: fork()\n");
        exit(0);
    }
    else if(pid>0)
    {
        close(fd1[0]);
        close(fd2[1]);
        while(fgets(line, MAXLINE, stdin)!=NULL)
        {
            n=strlen(line);
            if(write(fd1[1], line, n)!=n)
            {
                fprintf(stderr, "error: write to pipe\n");
                continue;
            }
            if((n=read(fd2[0], line, MAXLINE))<0)
            {
                fprintf(stderr, "error: read from pipe\n");
                continue;
            }
            if(n==0)
            {
                fprintf(stderr, "child closed pipe\n");
                break;
            }
            line[n]=0;
            if(fputs(line, stdout)==EOF)
            {
                fprintf(stderr, "error: fputs()\n");
            }
        }
        if(ferror(stdin))
        {
            fprintf(stderr, "error: fgets on stdin\n");
        }
        exit(0);
    }
    else
    {
        close(fd1[1]);
        close(fd2[0]);
        if(fd1[0] != STDIN_FILENO)
        {
            if(dup2(fd1[0], STDIN_FILENO)!=STDIN_FILENO)
            {
                fprintf(stderr, "error: dup2 to stdin\n");
                exit(0);
            }
            close(fd1[0]);
        }
        
        if(fd2[1]!=STDOUT_FILENO)
        {
            if(dup2(fd2[1], STDOUT_FILENO)!=STDOUT_FILENO)
            {
                fprintf(stderr, "error: dup2 to stdout\n");
                exit(0);
            }
            close(fd2[1]);
        }
        if(execl("./add2", "add2", (char *)0)<0)
        {
            fprintf(stderr, "error: execl\n");
        }
        exit(0);
    }
}

static void
sig_pipe(int signo)
{
    printf("SIGPIPE caught\n");
    exit(1);
}