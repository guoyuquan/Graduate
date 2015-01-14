#include<iostream>

class A{
public:
    ~A(){std::cout<<"destructor"<<std::endl;}
};

int main()
{
    A a;
    return 0;
}