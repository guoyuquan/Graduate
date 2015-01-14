#include<iostream>

class A{
public:
    virtual A * f(){std::cout<<"A's virtual f"<<std::endl; return this;}
};

class B: public A{
public:
    virtual B * f(){std::cout<<"B's virtual f"<<std::endl; return this;}
};

int main()
{
    A a;
    B b;
    A *pa=&a;
    pa->f();
    pa=&b;
    pa->f();
    return 0;
}