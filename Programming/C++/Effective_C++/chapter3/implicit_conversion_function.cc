#include<iostream>
#include<string>
class A
{
public:
    A():a(10){}
    A(int i):a(i){}
    explicit operator double(){return a;}
private:
    int a;
};

int main()
{
    A a;
    std::cout<<(double)a<<std::endl;
}