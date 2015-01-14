#include<stdio.h>

int main()
{
    int c, cnt;
    cnt=0;
    while((c=getchar())!=EOF)
    {
        if(c=='\n'||c==' '||c=='\t')
            ++cnt;
    }
    printf("%d\n",cnt);
}