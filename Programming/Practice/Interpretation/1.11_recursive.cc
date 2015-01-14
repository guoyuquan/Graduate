#include<iostream>

int func(int n)
{
    if(n<3)
        return n;
    return func(n-1)+2*func(n-2)+3*func(n-3);
}

int main()
{
    std::cout<<func(10)<<std::endl;
    return 0;
}