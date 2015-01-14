#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/file.h>
#include<unistd.h>

#define PERMS 0666

//void error(char *, ...);

int main(int argc, char *argv[])
{
    int f1, f2, n;
    char buf[BUFSIZ];
    if(argc!=3)
        printf("Usage: cp from tp");
    if((f1=open(argv[1], O_RDONLY, 0))==-1)
        printf("cp: can't open %s", argv[1]);
    if((f2=creat(argv[2], PERMS))==-1)
        printf("cp: can't create %s, mode %03o", argv[2], PERMS);
    while((n=read(f1,buf,BUFSIZ))>0)
        if(write(f2,buf,n)!=n)
            printf("cp: write error on file %s", argv[2]);
    return 0;
}