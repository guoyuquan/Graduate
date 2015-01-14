#include<iostream>

int i=10;
int j=i;
int fun()
{
    int k=100;
    std::cout<<"fun execute"<<std::endl;
    return k;
}
int f=fun();
int *p=new int(i);

int main()
{
    std::cout<<"f: "<<f<<std::endl;
    std::cout<<"i: "<<i<<"; j: "<<j<<std::endl;
    std::cout<<*p<<std::endl;
    return 0;
}