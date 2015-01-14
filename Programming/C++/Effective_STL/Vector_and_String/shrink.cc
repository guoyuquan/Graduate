#include<iostream>
#include<vector>
int main()
{
    std::vector<int> ivec;
    ivec.reserve(100);
    std::cout<<ivec.capacity()<<std::endl;
    std::vector<int>(ivec).swap(ivec);
    std::cout<<ivec.capacity()<<std::endl;
    return 0;
}
