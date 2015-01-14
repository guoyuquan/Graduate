#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif
#include <sys/ioctl.h>
#include <unistd.h>

static void
pr_winsize(int fd)
{
    struct winsize size;
    if(ioctl(fd, TIOCGWINSZ, (char *)&size)<0)
    {
        fprintf(stderr, "TIOCGWINSZ error\n");
        exit(0);
    }
    printf("%d rows, %d columns\n", size.ws_row, size.ws_col);
}

static void
sig_winch(int signo)
{
    printf("SIGWINCH received\n");
    pr_winsize(STDIN_FILENO);
}

int
main()
{
    if(isatty(STDIN_FILENO)==0)
        exit(0);
    if(signal(SIGWINCH, sig_winch)==SIG_ERR)
    {
        fprintf(stderr, "signal error\n");
        exit(0);
    }
    pr_winsize(STDIN_FILENO);
    for(;;)
        pause();
}