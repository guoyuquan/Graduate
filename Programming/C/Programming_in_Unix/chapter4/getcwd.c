#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char ptr[100];
    int size;
    if(chdir("/usr/spool/uucppublic")<0)
    {
        fprintf(stderr, "error: chdir\n");
        exit(0);
    }
    if(getcwd(ptr, 100)==NULL)
    {
        fprintf(stderr, "error: getcwd\n");
        exit(0);
    }
    printf("cwd = %s\n", ptr);
    return 0;
}