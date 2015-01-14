#include<iostream>
#include<stdexcept>

int main()
{
    try{
        std::bad_alloc ba;
        throw ba;
    }catch(...){
        std::cout<<"caught it"<<std::endl;
    }
    return 0;
}