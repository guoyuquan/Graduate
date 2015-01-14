#include<iostream>

int main()
{
    float f=0.001;
    float sum=0;
    for(int i=0; i<10; i++)
    {
        sum+=f;
        std::cout<<sum<<std::endl;
    }
    return 0;
}