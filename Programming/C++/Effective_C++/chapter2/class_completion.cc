#include<iostream>

class A
{
public:
    A &operator=(A a){return *this;}
    int what(A a);
private:
    
};

int main()
{
}