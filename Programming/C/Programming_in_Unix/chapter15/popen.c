#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PAGER "${PAGER:-more}"

#define MAXLINE 1024

int
main(int argc, char *argv[])
{
    char line[MAXLINE];
    FILE *fpin, *fpout;
    if(argc!=2)
    {
        fprintf(stderr, "usage: a.out <pathname>\n");
        exit(0);
    }
    if((fpin=fopen(argv[1], "r"))==NULL)
    {
        fprintf(stderr, "error: open %s\n", argv[1]);
        exit(0);
    }
    if((fpout=popen(PAGER, "w"))==NULL)
    {
        fprintf(stderr, "error: popen\n");
        exit(0);
    }
    while(fgets(line, MAXLINE, fpin)!=NULL)
    {
        if(fputs(line, fpout)==EOF)
        {
            fprintf(stderr, "error: fputs error to pipe\n");
            break;
        }
    }
    if(ferror(fpin))
    {
        fprintf(stderr, "error, fgets\n");
    }
    if(pclose(fpout)==-1)
        fprintf(stderr, "pclose error\n");
    exit(0);
}