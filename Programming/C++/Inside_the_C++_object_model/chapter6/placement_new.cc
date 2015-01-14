#include<iostream>

class A{
public:
    A():i(10){std::cout<<"A construct"<<std::endl;}
    ~A(){std::cout<<"A destruct"<<std::endl;}
    int fun(){return i;}
private:
    int i;
};



int main()
{
    A *p=(A *)operator new (10*sizeof(A));
    for(int i=0; i<10; i++)
        p[i]=A::A();
    //p->~A();
    std::cout<<"***"<<std::endl;
    //A::A();
    for(int i=0; i<10; ++i)
    {
        std::cout<<p[i].fun()<<std::endl;
        p[i].~A();
    }
    operator delete (p);
    return 0;
}