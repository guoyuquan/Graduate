#include<iostream>

class A{
public:
    A(){std::cout<<"A's constructor"<<std::endl;}
    void vir(){delete this;}
private:
    ~A(){std::cout<<"A's destructor"<<std::endl;}
};

int main()
{
    A *a=new A;
    a->vir();
    return 0;
}