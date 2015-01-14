#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int glob=6;
char buf[]="a write to stdout\n";

int main()
{
    int var;
    pid_t pid;
    var = 86;
    if(write(STDOUT_FILENO, buf, sizeof(buf)-1)!=sizeof(buf)-1)
    {
        fprintf(stderr, "write error\n");
        exit(0);
    }
    printf("before fork\n");
    if((pid=fork())<0)
    {
        fprintf(stderr, "error: fork\n");
        exit(0);
    }
    else if(pid==0)
    {
        glob++;
        var++;
    }
    else
    {
        sleep(2);
    }
    
    printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);
    return 0;
}