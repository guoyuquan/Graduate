#include<iostream>

class A{
public:
    static const int  fun() {i=11;return i;}
private:
    static int i;
};
int A::i=10;

int main()
{
    std::cout<<A::fun()<<std::endl;
    return 0;
}