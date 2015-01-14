#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
    if(argc!=2)
    {
        fprintf(stderr, "usage: a.out <pathname>\n");
        exit(0);
    }
    if(access(argv[1], R_OK)<0)
    {
        fprintf(stderr, "error: access for %s\n", argv[1]);
        //exit(0);
    }
    else
        printf("read access OK\n");
    if(open(argv[1], O_RDONLY)<0)
    {
        fprintf(stderr, "error: open %s\n", argv[1]);
    }
    else
        printf("open for reading OK\n");
    return 0;
}