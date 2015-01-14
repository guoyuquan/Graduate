#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void fun()
{
    printf("child exit\n");
}

int main()
{
    pid_t pid;
    atexit(fun);
    for(int i=0; i<10; i++)
    {
        if((pid=fork())<0)
        {
            fprintf(stderr, "error: fork\n");
            exit(0);
        }
        else if(pid==0)
        {
            printf("child%d\n", getpid());
            //sleep(1);
            //exit(0);
        }
    }
    //sleep(10);
    fork();
    return 0;
}