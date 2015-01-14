#include<iostream>

int main()
{
    std::cout<<std::string(typeid(double).name())<<std::endl;
    return 0;
}