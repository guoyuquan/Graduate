#include<iostream>

double product(int a, int b, int base)
{
    double sum=1;
    for(;a<=b; a+=base)
        sum*=a;
    return sum;
}

int factorial(int n)
{
    if(n<=0)
        return 1;
    return product(1,n,1);
}

double pi(int n)
{
    return 8*((product(4,n,2)*product(4,n,2))/(product(3,n,2)*product(3,n,2)));
}

int main()
{
    std::cout<<factorial(6)<<std::endl;
    std::cout<<pi(51)<<std::endl;
    return 0;
}