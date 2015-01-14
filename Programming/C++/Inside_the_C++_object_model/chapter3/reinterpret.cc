#include<iostream>

int main()
{
    long p=10;
    long *x=&p;
    long q=reinterpret_cast<long>(x);
    std::cout<<*(long *)q<<std::endl;
    std::cout<<sizeof (std::cout)<<std::endl;
    return 0;
}