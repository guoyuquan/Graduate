#include<iostream>

int main()
{
    int i(1024);
    int (*pf)(&i);
    std::cout<<i<<" "<<*pf<<" "<<pf<<std::endl;
    return 0;
}