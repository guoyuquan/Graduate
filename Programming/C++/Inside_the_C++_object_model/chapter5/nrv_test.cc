#include<iostream>

class A{
public:
    A(){std::cout<<"constructor"<<std::endl;}
};

A fun(){   
    A a;
    return a;
}

int main()
{
    A result=fun();
    return 0;
}