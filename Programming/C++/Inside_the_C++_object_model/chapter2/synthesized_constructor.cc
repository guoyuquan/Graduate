#include<iostream>

class A{
public:
    int func(){return i;}
    char * f(){return s;}
private:
    int i;
    char *s;
};

int main()
{
    A a;
    std::cout<<a.func()<<std::endl;
    std::cout<<a.f()<<std::endl;
    return 0;
}