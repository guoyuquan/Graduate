#include<iostream>

int main()
{
    int i=0;
    goto sta;
    
    for(i=0; i<10; i++)
    {
    sta:
        std::cout<<6<<std::endl;
    }
    i=0;
    goto s;
    while(i<10)
    {
    s:
        std::cout<<66<<std::endl;
    }
    return 0;
}