#include<stdio.h>

#define MAX 10
int main()
{
    char c[MAX];
    char ch;
    for(int i=0;((i<MAX-1)+((ch=getchar())!='\n')+(ch!=EOF))==3;++i)
        c[i]=ch;
    printf("%s\n",c);
}