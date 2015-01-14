#include<iostream>

class A{
public:
    virtual void f1(){std::cout<<"I'm f1"<<std::endl;}
    virtual void f2(){std::cout<<"I'm f2"<<std::endl;}
    virtual void f3(){std::cout<<"I'm f3"<<std::endl;}
};

class B: public A{
};
typedef void (*f)();
int main()
{
    std::cout<<"size of A"<<sizeof (A)<<std::endl;
    A a;
    A *p=&a;
    long* pol=reinterpret_cast<long *>(p);
    std::cout<<"vptr: "<<(long)pol<<std::endl;
    std::cout<<"first element of vtable: "<<*pol<<std::endl;
    std::cout<<"second element of vtable:";
    ((f)*((long *)*(pol)))();
    std::cout<<pol<<std::endl;
    pol++;
    pol++;
    std::cout<<pol<<std::endl;
    //((f)*((long *)*(pol)))();
    //((f)*((long *)*(pol+2)))();
    return 0;
}