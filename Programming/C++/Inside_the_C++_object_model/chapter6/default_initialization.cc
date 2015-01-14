#include<iostream>

int i;

int fun()
{
    int j;
    return j;
}

int main()
{
    int j;
    std::cout<<"i: "<<i<<"; "<<"j: "<<j<<"; in function: "<<fun()<<std::endl;
    return 0;
}