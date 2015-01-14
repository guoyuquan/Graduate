#include<iostream>

int main()
{
    int i=10;
    ++i=9;
    //i++=10;//error
    std::cout<<i<<std::endl;
    std::cout<<(++i)++<<std::endl;
    std::cout<<i<<std::endl;
    return 0;
}