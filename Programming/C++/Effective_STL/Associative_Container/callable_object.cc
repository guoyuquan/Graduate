#include<iostream>
#include<set>

typedef bool (*f) (int, int);

int main()
{
    std::set<int, f> iset;
    return 0;
}