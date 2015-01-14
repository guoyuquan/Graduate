#include<iostream>
#include<assert.h>



class A{
public:
    A():a(1),b(2),c(3){}
    int a;

private:
    int c;
protected:
    int b;
};

int main()
{
    A a;
    A *p=&a;
    int *p1=reinterpret_cast<int *>(p);
    std::cout<<*p1<<std::endl;
    std::cout<<*(p1+1)<<std::endl;
    std::cout<<*(p1+2)<<std::endl;
    return 0;
}