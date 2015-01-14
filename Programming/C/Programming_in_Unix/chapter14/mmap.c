#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char * argv[])
{
    int fdin, fdout;
    void *src, *dst;
    struct stat statbuf;
    if(argc != 3)
    {
        fprintf(stderr, "usage: %s <fromfile> <tofile>\n", argv[0]);
        exit(0);
    }
    if((fdin=open(argv[1], O_RDONLY))<0)
    {
        fprintf(stderr, "error: cannot open %s for reading\n", argv[1]);
        exit(0);
    }
    if((fdout=open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILESEC_MODE))<0)
    {
        fprintf(stderr, "error: cannot create %s for writing\n", argv[2]);
        exit(0);
    }
    if(fstat(fdin, &statbuf)<0)
    {
        fprintf(stderr, "fstat error\n");
        exit(0);
    }
    if(lseek(fdout, statbuf.st_size-1, SEEK_SET)==-1)
    {
        fprintf(stderr, "lseek error\n");
        exit(0);
    }
    if(write(fdout, "", 1)!=1)
    {
        fprintf(stderr, "write error\n");
        exit(0);
    }
    if((src=mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0))==MAP_FAILED)
    {
        fprintf(stderr, "mmap error for inputn");
        exit(0);
    }
    if((dst=mmap(0, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fdout, 0))==MAP_FAILED)
    {
        fprintf(stderr, "mmap error for output\n");
        exit(0);
    }
    memcpy(dst, src, statbuf.st_size);
    exit(0);
}