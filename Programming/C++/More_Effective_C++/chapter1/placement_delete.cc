#include<iostream>

class test{
public:
    test(){std::cout<<"constructor is called"<<std::endl;}
    ~test(){std::cout<<"destructor is called"<<std::endl;}
};

int main()
{
    test *p=static_cast<test *>(operator new [] (10*sizeof(test)));
    operator delete []( p);
    return 0;
}