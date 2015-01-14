#include<stdio.h>

unsigned int setbits(int x,int p, int n, int y);

int main()
{
    printf("%d\n",setbits(15,2,2,2));
    return 0;
}

unsigned int setbits(int x, int p, int n, int y)
{
    x=x&((~0<<p)|~(~0<<(p-n+1)));
    y=y&(~(~0<<p)|~(~0<<(p-n+1)));
    return x|y;
}