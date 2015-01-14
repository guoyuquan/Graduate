#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

int main()
{
    char buf[256];
    pid_t pid;
    int status;
    printf("%% ");
    while (fgets(buf, 256, stdin)!=NULL)
    {
        if(buf[strlen(buf)-1]=='\n')
            buf[strlen(buf)-1]=0;
        if((pid=fork())<0)
        {
            fprintf(stderr, "error: create child process\n");
            exit(0);
        }
        else if(pid==0)
        {
            execlp(buf, buf, (char *)0);
            fprintf(stderr, "couldn't execute: %s \n", buf);
            exit(127);
        }
        if((pid=waitpid(pid, &status, 0))<0)
            fprintf(stderr, "error: wait child process\n");
        printf("%% ");
    }
    exit(0);
}