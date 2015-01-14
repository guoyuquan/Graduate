#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void err_sys(char *s)
{
    fprintf(stderr, "%s\n", s);
    exit(0);
}

int main()
{
    int      status;
    
    if ((status = system("date")) < 0)
        err_sys("system() error");
    //pr_exit(status);
    
    if ((status = system("nosuchcommand")) < 0)
        err_sys("system() error");
    //pr_exit(status);
    
    if ((status = system("who; exit 44")) < 0)
        err_sys("system() error");
    //pr_exit(status);
    
    exit(0);
}