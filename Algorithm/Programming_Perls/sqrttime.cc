#include <iostream>
#include <stdlib.h>
#include <math.h>

int main()
{
    clock_t time=clock();
    float s;
    for(int i=0; i<100000000; i++)
        s=sqrt(10.0);
    std::cout<<clock()-time<<"miliseconds"<<std::endl;
    return 0;
}