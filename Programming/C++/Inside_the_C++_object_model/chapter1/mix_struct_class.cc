#include<iostream>

class A{
public:
    A(){std::cout<<"I'm class"<<std::endl;}
};

struct B: public A{
    B(){std::cout<<"I'm struct"<<std::endl;}
};

int main()
{
    B b;
    return 0;
}