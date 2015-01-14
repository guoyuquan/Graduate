#include<iostream>

double multiply(double base, int n)
{
    bool flag;
    if(n%2!=0)
        flag=true;
    else flag=false;
    double sum=base;
    while((n=n/2)>0)
        sum+=sum;
    if(flag)
        return base+sum;
    return sum;
}

int main()
{
    std::cout<<multiply(10,4)<<std::endl;
    return 0;
}