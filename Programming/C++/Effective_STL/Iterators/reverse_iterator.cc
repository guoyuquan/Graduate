#include<iostream>
#include<vector>

int main()
{
    std::vector<int> ivec;
    for(int i=0; i<10; i++)
        ivec.push_back(i);
    std::vector<int>::reverse_iterator rit;
    rit=find(ivec.rbegin(), ivec.rend(), 6);
    std::cout<<*rit<<std::endl;
    std::cout<<*rit.base()<<std::endl;
    return 0;
}