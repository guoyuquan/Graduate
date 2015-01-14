#include<fcntc.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

void filecopy(FILE *, FILE *);

int main(int argc, char *argv[])
{
    if(argc==1)
        filecopy(stdin, stdout);
}

void filecopy(FILE * fp1, FILE * fp2)
{
    int c;
    while((c=getc(fp1))!=EOF)
        putc(c, fp2);
}