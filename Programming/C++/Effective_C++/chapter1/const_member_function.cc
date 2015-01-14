#include<iostream>

class A
{
public:
    const int  fun(){std::cout<<"I am non-const."<<std::endl; return 0;}
    const int  fun() const  {std::cout<<"I am const."<<std::endl; return 0;}
};
int main()
{
    A a1;
    const A a2=a1;
    a1.fun();
    a2.fun();
    return 0;
}