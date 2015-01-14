#include<iostream>

int gcd(int m, int n);

int main()
{
    std::cout<<gcd(1989, 1590)<<std::endl;
    return 0;
}

int gcd(int m, int n)
{
    int rem;
    while(n>0)
    {
        rem=m%n;
        m=n;
        n=rem;
    }
    return m;
}