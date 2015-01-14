#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;
    if(argc!=2)
    {
        fprintf(stderr, "error: missing arguments\n");
        exit(1);
    }
    if((dp=opendir(argv[1]))==NULL)
       fprintf(stderr, "error: open %s\n", argv[1]);
    while ((dirp=readdir(dp))!=NULL)
        printf("%s\n", dirp->d_name);
    closedir(dp);
    return 0;
}