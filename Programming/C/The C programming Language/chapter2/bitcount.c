#include<stdio.h>

int main()
{
    int i=31;
    int j;
    for(j=1;i&=(i-1);++j);
    printf("%d\n",j);
    return 0;
}