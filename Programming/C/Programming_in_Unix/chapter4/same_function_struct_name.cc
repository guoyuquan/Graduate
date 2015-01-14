#include<iostream>

struct fun{
    int i;
};

int fun()
{
    std::cout<<"just a test"<<std::endl;
    return 0;
}

int main()
{
    struct fun s;
    fun();
    return 0;
}
