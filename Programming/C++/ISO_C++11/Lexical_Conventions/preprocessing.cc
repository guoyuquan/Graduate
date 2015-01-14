#define R "x"
char c[10]=R"y";

#include <iostream>

int main()
{
    std::cout<<c<<std::endl;
}