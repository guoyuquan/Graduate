#include<iostream>

class A{
public:
    explicit operator double (){return 10.0;}
};

int main()
{
    A a;
    std::cout<<double(a)<<std::endl;
    return 0;
}