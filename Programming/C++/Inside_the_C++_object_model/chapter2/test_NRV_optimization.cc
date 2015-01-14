#include<iostream>

class A{
public:
    A(){std::cout<<"constructor"<<std::endl;}
    A(A & a, int j){std::cout<<"copy constructor"<<std::endl;}
};

A fun()
{
    A a;
    return a;
}

int main()
{
    A a;
    a=fun();
    return 0;
}