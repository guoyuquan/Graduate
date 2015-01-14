#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void set_fl(int fd, int flags)
{
    int val;
    if((val=fcntl(fd, F_GETFL, 0))<0)
    {
        fprintf(stderr, "error: fcntl F_GETFL\n");
        exit(0);
    }
    val |= flags;
    if(fcntl(fd, F_SETFL, val) < 0)
    {
        fprintf(stderr, "error: fcntl F_SETFL\n");
        exit(0);
    }
}