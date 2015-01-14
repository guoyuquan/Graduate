#include<iostream>

class A
{
public:
    int fun(){return 1;}
};

class B: public A
{
public:
    using A::fun;
    int fun(){return 2;}
};
int main()
{
    B a;
    std::cout<<a.A::fun()<<std::endl;
}