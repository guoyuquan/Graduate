#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define BUFFSIZE 4096

int main()
{
    int n;
    char buf[BUFFSIZE];
    while((n=read(STDIN_FILENO, buf, BUFFSIZE))>0)
    {
        if(write(STDOUT_FILENO, buf, n)!=n)
        {
            fprintf(stderr, "error: write to STDOUT\n");
            exit(0);
        }
    }
    if(n<0)
    {
        fprintf(stderr,"error:read, less than 1\n");
        exit(0);
    }
    return 0;
}