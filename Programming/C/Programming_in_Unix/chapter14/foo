#include <stropts.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int
isastream(int fd)
{
    return (ioctl(fd, I_CANPUT, 0)!=-1);
}

int
main(int argc, char *argv[])
{
    int i, fd;
    for(i=1; i<argc; i++)
    {
        if((fd=open(argv[i], O_RDONLY))<0)
        {
            fprintf(stderr, "error: can't open %s\n", argv[i]);
            continue;
        }
        if(isastream(fd)==0)
        {
            fprintf(stdout, "%s: not a stream\n", argv[i]);
        }
        else
        {
            fprintf(stdout, "%s: streams device\n", argv[i]);
        }
    }
    exit(0);
}