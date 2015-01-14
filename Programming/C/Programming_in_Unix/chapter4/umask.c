#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main()
{
    umask(0);
    if(creat("foo", RWRWRW)<0)
    {
        fprintf(stderr, "error: creat for foo\n");
        exit(0);
    }
    umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if(creat("bar", RWRWRW)<0)
    {
        fprintf(stderr, "error: creat for bar\n");
        exit(0);
    }
    return 0;
}