#include<iostream>
#include<vector>

int main()
{
    std::vector<bool> bvec;
    bvec.push_back(true);
    //bool *p=&bvec[0];
    std::cout<<sizeof(bool)<<std::endl;
    return 0;
}