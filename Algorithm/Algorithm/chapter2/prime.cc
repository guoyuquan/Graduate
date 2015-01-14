#include<iostream>
#include<cmath>

bool prime(int num)
{
    int div=sqrt(num);
    bool pri=true;
    for(int i=2; i<=div; i++)
        if(num%i==0)
            pri=false;
    return pri;
}

int main()
{
    std::cout<<prime(7)<<std::endl;
    return 0;
}