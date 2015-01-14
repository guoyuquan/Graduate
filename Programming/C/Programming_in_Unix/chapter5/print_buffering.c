#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void pr_stdio(const char *, FILE *);

int main()
{
    FILE * fp;
    fputs("enter any character\n", stdout);
    if(getchar()==EOF)
    {
        fprintf(stderr,"error: getchar, encounter EOF\n");
        exit(0);
    }
    fputs("one line to standard error\n", stderr);
    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);
    if((fp=fopen("/etc/motd", "r"))==NULL)
    {
        fprintf(stderr, "error, fopen %s\n", strerror(errno));
        exit(0);
    }
    if(getc(fp)==EOF)
    {
        fprintf(stderr, "error: getc\n");
        exit(0);
    }
    pr_stdio("/etc/motd", fp);
    return 0;
}

void pr_stdio(const char *name, FILE *fp)
{
    printf("stream = %s, ", name);
    if(fp->_flags&__SNBF)
        printf("unbuffered");
    else if(fp->_flags&__SLBF)
        printf("line buffered");
    else
        printf("fully buffered");
    printf(", buffer size = %d\n", fp->_lbfsize);
}