#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 1024

int
main()
{
    int n, int1, int2;
    char line[MAXLINE];
    
    while((n=read(STDIN_FILENO, line, MAXLINE))>0)
    {
        line[n]=0;
        if(sscanf(line, "%d%d", &int1, &int2)==2)
        {
            sprintf(line, "%d\n", int1+int2);
            n=strlen(line);
            if(write(STDOUT_FILENO, line, n)!=n)
            {
                fprintf(stderr, "write error\n");
                exit(0);
            }
        }
        else
        {
            if(write(STDOUT_FILENO, "invalid argc\n", 13)!=13)
            {
                fprintf(stderr, "write error\n");
                exit(0);
            }
        }
    }
    exit(0);
}
