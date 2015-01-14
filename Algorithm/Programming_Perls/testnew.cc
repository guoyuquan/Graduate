#include <iostream>

struct i
{
    int i;
};

int main()
{
    i *p=new i[10];
    std::cout<<sizeof(i)<<std::endl;
    std::cout<<p<<std::endl;
    std::cout<<&p[10]<<std::endl;
    return 0;
}