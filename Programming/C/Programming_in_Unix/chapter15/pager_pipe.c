#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 1024

int main(int argc, char * argv[])
{
    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line [MAXLINE];
    FILE *fp;
    if(argc != 2)
    {
        fprintf(stderr, "usage: a.out <pathname>\n");
        exit(0);
    }
    if((fp=fopen(argv[1], "r"))==NULL)
    {
        fprintf(stderr, "error: can't open %s", argv[1]);
        exit(0);
    }
    if(pipe(fd)<0)
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
        close(fd[0]);
        while(fgets(line, MAXLINE, fp)!=NULL)
        {
            n=strlen(line);
            if(write(fd[1], line, n)!=n)
            {
                fprintf(stderr, "error: write to pipe\n");
                break;
            }
        }
        if(ferror(fp))
        {
            fprintf(stderr, "fgets error\n");
        }
        close(fd[1]);
        if(waitpid(pid, NULL, 0)<0)
        {
            fprintf(stderr, "waitpid error\n");
        }
        exit(0);
    }
    else
    {
        close(fd[1]);
        if(fd[0]!=STDIN_FILENO)
        {
            if(dup2(fd[0], STDIN_FILENO)!=STDIN_FILENO)
            {
                fprintf(stderr, "dup2 error to stdin\n");
                exit(0);
            }
            close(fd[0]);
        }
        pager="/usr/bin/more";
        argv0="more";
        if(execl(pager, argv0, (char *)0)<0)
        {
            fprintf(stdout, "execl error for %s", pager);
        }
    }
    exit(0);
}