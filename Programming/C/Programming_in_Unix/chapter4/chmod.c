#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct stat statbuf;
    if(stat("foo", &statbuf)<0)
    {
        fprintf(stderr, "error: stat for foo\n");
        exit(0);
    }
    if(chmod("foo", (statbuf.st_mode &~S_IXGRP)|S_ISGID)<0)
    {
        fprintf(stderr, "error: chmod for foo\n");
        exit(0);
    }
    if(chmod("bar", S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)<0)
    {
        fprintf(stderr, "error: chmod for bar\n");
    }
    return 0;
}