#include<iostream>

class A{
public:
    A(int a1, int c1):a(a1), c(c1){}
    int ar(){return a;}
private:
    int a;
    static int b;
    int c;
};

int main()
{
    A a(10, 11);
    A *p=&a;
    int *p1=reinterpret_cast<int *>(p);
    *p1=20;
    std::cout<<*p1<<" "<<sizeof (int)<<std::endl;
    //p1=reinterpret_cast<int *>(p+1);
    std::cout<<*(p1+1)<<std::endl;
    std::cout<<a.ar()<<std::endl;
    return 0;
}