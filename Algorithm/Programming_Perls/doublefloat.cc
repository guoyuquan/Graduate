#include <iostream>
#include <stdlib.h>

int main()
{
    double x=3.66;
    clock_t start=clock();
    for(int i=0; i<10000000; i++)
        x*=x;
    std::cout<<clock()-start<<"milisecond"<<std::endl;
    float y=3.66;
    start=clock();
    for(int i=0; i<10000000; i++)
        y*=y;
    std::cout<<clock()-start<<"milisecond"<<std::endl;
    return 0;
}