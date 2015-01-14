#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main(int argc, char **argv)
{
    int c;
    if(strcmp(*argv, "./upper")==0)
        while((c=getchar())!=EOF)
            putchar(toupper(c));
    else
        while((c=getchar())!=EOF)
            putchar(tolower(c));
    return 0;
}