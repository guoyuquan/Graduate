#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        fprintf(stderr, "usage: a.out <descriptor#>\n");
        exit(0);
    }
    int val;
    if((val=fcntl(atoi(argv[1]), F_GETFL, 0))<0)
    {
        fprintf(stderr, "error: fcntl for fd %d\n", atoi(argv[1])); 
        exit(0);
    }
    switch (val & O_ACCMODE)
    {
        case O_RDONLY :
            printf("read only");
            break;
        case O_WRONLY :
            printf("write only");
            break;
        case O_RDWR :
            printf("read write");
            break;
        default :
            fprintf(stderr, "unknown access mode");
            exit(0);
    }
    if(val & O_APPEND)
        printf(", append");
    if(val & O_NONBLOCK)
        printf(", nonblocking");
#if defined(O_SYNC)
    if(val & O_SYNC)
        printf(", synchrounous writes");
#endif
    
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
    if(val & O_FSYNC)
        printf(", synchronous writes");
#endif
    putchar('\n');
    return 0;
}