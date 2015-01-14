#include<iostream>

class A
{
    int i;
};

class B:public A{
public:
    B(){i=10; std::cout<<i<<std::endl;}
};

int main()
{
    B b;
    return 0;
}