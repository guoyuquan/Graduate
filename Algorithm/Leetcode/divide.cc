#include <iostream>

int rec(int dividend, int divisor)
{
    if(dividend<divisor)
        return 0;
    if(dividend==divisor)
        return 1;
    int i=1, j=divisor;
    while(dividend>divisor)
    {
        divisor<<=1;
        i<<=1;
    }
    std::cout<<dividend<<std::endl;
    divisor>>=1;
    i>>=1;
    dividend-=divisor;
    i+=3*rec(dividend, j+j+j);
    return i;
}

int main()
{
    std::cout<<rec(2147483647, 2);
    return 0;
}