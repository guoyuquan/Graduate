#include<iostream>

class A{
public:
    A(){std::cout<<"constructor is called"<<std::endl;}
};

int main()
{
    A *pa=static_cast<A *>(operator new(sizeof(A)));
    pa=new(pa)A();
    operator delete (pa);
    return 0;
}