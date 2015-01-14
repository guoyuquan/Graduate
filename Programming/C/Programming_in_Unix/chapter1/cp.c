#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define BUFFSIZE 4096

int main()
{
    int n;
    char buf[BUFFSIZE];
    while((n=read(STDIN_FILENO, buf, BUFFSIZE))>0)
        if(write(STDOUT_FILENO, buf, n)!=n)
            fprintf(stderr, "write error\n");
        if(n<0)
            fprintf(stderr, "read error");
    exit(0);
}