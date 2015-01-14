#include<iostream>
#include<cmath>
#include<time.h>

bool prime(int n)
{
    int tar=sqrt(n);
    for(int i=2; i<tar; i++)
        if(n%i==0)
            return false;
    return true;
}

bool fast_prime(int n)
{
    int tar=sqrt(n);
    if(n%2==0)
        return false;
    for(int i=3; i<tar; i+=2)
        if(n%i==0)
            return false;
    return true;
}

int main()
{
    time_t t1=time(&t1);
    std::cout<<prime(10000001)<<std::endl;
    time_t t2=time(&t2);
    std::cout<<fast_prime(10000001)<<std::endl;
    time_t t3=time(&t3);
    std::cout<<difftime(t1, t2)<<" "<<difftime(t2, t3)<<std::endl;
}