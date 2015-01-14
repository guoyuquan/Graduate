#include<iostream>

int gcd(int m, int n)
{
    int div;
    for(int i=0; true; i++)
    {
        div=m%n;
        if(div==0)
            return n;
        m=n;
        n=div;
    }
    return div;
}

int main()
{
    std::cout<<gcd(10, 15)<<std::endl;
    return 0;
}