#include<iostream>

int main()
{
    int i=10;
    const int *p=&i;
    int *q=const_cast<int *>(p);
    int *ptr=(int *)p;
    *q=5;
    std::cout<<i<<std::endl;
    *ptr=6;
    std::cout<<i<<std::endl;
    return 0;
}