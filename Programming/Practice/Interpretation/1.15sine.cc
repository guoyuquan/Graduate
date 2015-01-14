#include<iostream>
#include<cmath>

double sine(double x);

int main()
{
    sine(10);
    std::cout<<sine(12.15)<<std::endl;
    return 0;
}

double p(double x)
{
    static int i=1;
    std::cout<<i++<<std::endl;
    return 3*x-4*x*x*x;
}

double sine(double x)
{
    if(abs(x)<0.1)
        return x;
    return p(sine(x/3));
}