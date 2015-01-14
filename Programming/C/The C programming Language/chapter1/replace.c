#include<stdio.h>

int main()
{
    int c, cnt;
    while((c=getchar())!=EOF)
    {
        if(c=='\n'||c=='\t')
            putchar(' ');
        else
            putchar(c);
    }
}