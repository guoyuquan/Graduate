#include<iostream>
#include<vector>

int main()
{
    std::vector<int> ivec;
    ivec.reserve(10);
    ivec[1]=10;
    for(int i=0; i<10 ;i++)
        std::cout<<ivec[i]<<" ";
    std::cout<<std::endl;
    std::cout<<ivec.size()<<std::endl;
    return 0;
}