#include<stdio.h>

#define swap(t,x,y)  t temp; temp=x; x=y; y=temp;

int main()
{
    int i1=10;
    int i2=20;
    int *p1=&i1, *p2=&i2;
    printf("%d %d\n",*p1,*p2);
    swap(int *, p1, p2);
    printf("%d %d\n",*p1,*p2);
    return 0;
}