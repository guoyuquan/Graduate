#include<iostream>

class A{
public:
    virtual void fun(){std::cout<<"A"<<std::endl;}
};

class B: public A{
public:
    virtual void fun(){std::cout<<"B"<<std::endl;}
};

int main()
{
    B b;
    A *a=&b;
    A aa=*a;
    aa.fun();
    a->fun();
    return 0;
}