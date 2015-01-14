#include <pwd.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void my_alarm(int signo)
{
    struct passwd *rootptr;
    printf("in signal handler\n");
    if((rootptr=getpwnam("root"))==NULL)
    {
        fprintf(stderr, "error: getpwname(root)\n");
        exit(0);
    }
    alarm(1);
}

int main()
{
    struct passwd * ptr;
    signal (SIGALRM, my_alarm);
    alarm(1);
    for(; ;)
    {
        printf("***\n");
        if((ptr=getpwnam("JERRY"))==NULL)
           {
               fprintf(stderr, "error: getpwnam(jerry)\n");
               exit(0);
           }
        if(strcmp(ptr->pw_name, "JERRY")!=0)
            printf("return value corrupted!\n");
    }
    return 0;
}