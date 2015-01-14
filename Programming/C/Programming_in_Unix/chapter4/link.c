#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    if(open("tempfile", O_RDWR|O_CREAT)<0)
    {
        fprintf(stderr, "error: open\n");
        exit(0);
    }
    if(unlink("tempfile")<0)
    {
        fprintf(stderr, "error: unlink\n");
        exit(0);
    }
    printf("file unlinked\n");
    sleep(15);
    printf("done\n");
    return 0;
}