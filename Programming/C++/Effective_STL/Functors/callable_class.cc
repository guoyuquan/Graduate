#include<iostream>

class A{
public:
    A(int, int){}
    void operator()(){std::cout<<"call"<<std::endl;}
};

int main()
{
    A a(0, 0);
    a();
}