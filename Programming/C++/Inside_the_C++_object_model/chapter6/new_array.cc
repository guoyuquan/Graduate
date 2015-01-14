#include<iostream>

int main()
{
    int *p=new int[10];
    short *q=reinterpret_cast<short *>(p);
    q--;
    std::cout<<p<<" "<<q<<std::endl;
    std::cout<<*q<<std::endl;
    delete []p;
    return 0;
}