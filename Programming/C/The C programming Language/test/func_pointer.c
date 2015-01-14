#include<stdio.h>

void print()
{
    printf("haha\n");
}

int main()
{
    void (*p)()=print;
    (*p)();
    p();
    print();
    (*print)();
    return 0;
}