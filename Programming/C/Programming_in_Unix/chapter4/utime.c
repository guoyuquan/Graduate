#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int i, fd;
    struct stat statbuf;
    struct utimbuf timebuf;
    for (i=1; i<argc; i++)
    {
        if(stat(argv[i], &statbuf)<0)
        {
            fprintf(stderr, "error: stat %s\n", argv[i]);
            continue;
        }
        if((fd=open(argv[i], O_RDWR|O_TRUNC))<0)
        {
            fprintf(stderr, "error: open %s\n", argv[i]);
            continue;
        }
        close(fd);
        timebuf.actime=statbuf.st_atime;
        timebuf.modtime=statbuf.st_mtime;
        if(utime(argv[i], &timebuf)<0)
        {
            fprintf(stderr, "error: utime %s\n", argv[i]);
            continue;
        }
    }
    return 0;
    
}