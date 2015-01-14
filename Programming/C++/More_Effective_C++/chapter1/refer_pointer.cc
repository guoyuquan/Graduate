#include<iostream>

int main()
{
    int *p=0;
    int * &r=p;
    int c='a';
    p=&c;
    std::cout<<*r<<r<<std::endl;
    return 0;
}