#include<iostream>

int main()
{
    int *p =new int[1000000000000];
    for(int i=0; ; i++)
        std::cout<<p[i]<<" ";
    delete[] p;
}