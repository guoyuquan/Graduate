#include<iostream>
using std::cout;
using std::endl;


class B
{
public:
    virtual void fun1(){cout<<"fun1"<<endl;}
    virtual void fun2(){cout<<"fun2"<<endl;}
};

typedef void (*func)();
int main()
{
    B b;
    void (*f)()=(void (*)())*((long *)*(long *)(&b));//64bits OS~ ~ ~
    f();
    //int (*f)();
    //f=(void *)fun;
    //f(1);
    return 0;
}