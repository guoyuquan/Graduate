#include<iostream>

class A
{
public:
    int fun(){return i;}
private:
    static int i;
};
int A::i=0;

int main()
{
    A a;
    std::cout<<a.fun();
}