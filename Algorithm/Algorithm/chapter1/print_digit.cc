#include<iostream>

template <typename T>
void print(T t);

int main()
{
    print(1997);
    return 0;
}

template <typename T>
void print(T t)
{
    if(t<=9)
    {
        std::cout<<t;
        return;
    }
    print(t/10);
    std::cout<<t%10;
}