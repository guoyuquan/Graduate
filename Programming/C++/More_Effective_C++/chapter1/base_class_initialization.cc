#include<iostream>

class A{
public:
    A(int a){std::cout<<"A's constuctor"<<std::endl;}
};

class B:public A{
public:
    B(int a=0):A(a){std::cout<<"b's constructor"<<std::endl;}
};

class C: public B{
};

int main()
{
    B b;
    C c;
    return 0;
}