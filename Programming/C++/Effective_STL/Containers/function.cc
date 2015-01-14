#include<iostream>

int fun(double (a))
{
    std::cout<<"double (a)"<<std::endl;
    return 0;
}
int fun(double ())
{
    std::cout<<"double ()"<<std::endl;
    return 0;
}
int fun(int p())
{
    std::cout<<"double p()"<<std::endl;
    return 0;
}
int main()
{
    double (*p)();
    fun((1));
    fun(p);
}