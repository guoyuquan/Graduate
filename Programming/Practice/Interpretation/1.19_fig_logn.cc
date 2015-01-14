#include<iostream>

int real_fib(int a, int b, int p, int q, int n)
{
    if(n==0)
        return b;
    if(n%2==0)
        return real_fib(a, b, p*p+q*q, 2*p*q+q*q, n/2);
    else
        return real_fib(b*q+a*q+a*p, b*p+a*q, p, q, n-1);
}

int fib(int n)
{
    return real_fib(1, 0, 0, 1, n);
}

int main()
{
    std::cout<<fib(10000)<<std::endl;
    return 0;
}