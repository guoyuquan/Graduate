#include<iostream>

int main()
{
    void *pi=operator new [](10*sizeof(int));
    int *p=static_cast<int *>(pi);
    for(int i=0; i<10; i++)
        p[i]=i;
    for(int i=0; i<10; i++)
        std::cout<<p[i]<<" ";
    std::cout<<std::endl;
    return 0;
}