#include<iostream>

class A
{
public:
    A(int & j):i(j){}
private:
    int &i;
};

int main()
{
    int i;
    A a1(i), a2(i);
    a1=a2; //error: no copy assinment function would be generated by the compiler
    //error: cannot define the implicit copy assignment
    //operator for 'A', because non-static reference member 'i' can't use copy
    //    assignment operator

    return 0;
}