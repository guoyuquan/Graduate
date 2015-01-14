#include <string>
#include <iostream>

int main()
{
    std::string str="";
    std::cout<<str.size()<<std::endl;
    std::cout<<"";
    char *p="";
    std::cout<<*p;
    
    int i=*p;
    std::cout<<i<<std::endl;
    return 0;
}