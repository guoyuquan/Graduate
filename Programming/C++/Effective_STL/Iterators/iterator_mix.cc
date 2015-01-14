#include<iostream>
#include<vector>

int main()
{
    std::vector<int> ivec;
    std::vector<int>::iterator it1=ivec.begin();
    std::vector<int>::const_iterator it2=ivec.cbegin();
    if(it1==it2)
        std::cout<<"support"<<std::endl;
    if(it2==it1)
        std::cout<<"also support"<<std::endl;
    std::cout<<it2-it1<<std::endl;
    return 0;
}