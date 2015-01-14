#include<iostream>

int main()
{
    int *p=new int(10);
    delete p;
    *p=11;
    std::cout<<*p<<std::endl;
    return 0;
}