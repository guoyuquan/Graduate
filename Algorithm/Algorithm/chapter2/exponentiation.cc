#include<iostream>

int expr(int base, int p);

int main()
{
    std::cout<<expr(2, 3)<<" "<<expr(2,4)<<std::endl;
    return 0;
}

int expr(int base, int n)
{
    int sum=base;
    while(n/2>0)
    {
        sum*=sum;
        n/=2;
    }
    return n==1?sum*base:sum;
}