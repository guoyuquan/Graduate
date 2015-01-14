#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    if(chdir("/tmp")<0)
    {
        fprintf(stderr, "error: chdir\n");
        exit(0);
    }
    printf("chdir to /tmp succeeded\n");
    return 0;
}