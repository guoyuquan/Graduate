#include<iostream>

class A
{
public:
    void fun(){};
private:
    int i;
};

class B
{
};

int main()
{
    A *a;
    B *b;
    char *c;
    std::cout<<sizeof (a)<<" "<<sizeof(b)<<" "<<sizeof(c)<<std::endl;
    std::cout<<sizeof(A)<<" "<<sizeof(B)<<std::endl;
}