#include<iostream>

typedef int (*iif)(int);
int f(iif fi) 
{
    return fi(2);
    
}

int fun(int i)
{
    return i;
}

int main()
{
    int (*g) (iif);
    g=f;
    f(g);
    return 0;
}