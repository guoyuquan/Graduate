#include<iostream>

class A{
    virtual void f(){}
};
class B{
    virtual void f(){}
};

class C:public A, public B{
};

int main()
{
    std::cout<<sizeof (C)<<std::endl;
}