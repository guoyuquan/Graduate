#include<iostream>

typedef int xxx;

class A{
    
public:
    void x(xxx y){std::cout<<y<<std::endl;} //use the global one
private:
    typedef float xxx;
};

int main()
{
    A a;
    a.x(10);
    a.x(10.111);
    return 0;
}