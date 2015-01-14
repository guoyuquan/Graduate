#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main()
{
    int fd;
    if((fd=creat("file.hole", FILESEC_MODE))<0)
    {
        fprintf(stderr, "create error\n");
        exit(0);
    }
    if(write(fd, buf1, 10)!=10)
    {
        fprintf(stderr, "buf1 write error\n");
        exit(0);
    }
    if(lseek(fd, 16386, SEEK_SET)==-1)
    {
        fprintf(stderr, "error: lseek\n");
        exit(0);
    }
    if(write(fd, buf2, 10)!=10)
    {
        fprintf(stderr, "error: write buf2\n");
        exit(0);
    }
    return 0;
}
