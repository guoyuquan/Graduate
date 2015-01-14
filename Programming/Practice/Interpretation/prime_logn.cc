#include<iostream>
#include<utility>

int expr(int base, int exp)
{
    int temp;
    if(exp==0)
        return 1;
    if(exp%2==0)
        temp=expr(base, exp/2);
    else
    {
        temp=base* expr(base, exp-1);
    }
    return temp;
}

bool try_it(int a, int n)
{
    if(expr(a, n)%n==a)
        return true;
    return false;
}

bool fermat_test(int n)
{
    return try_it(random()%n, n);
}

bool fast(int n, int times)
{
    if(times==0)
        return true;
    else if(fermat_test(n))
        fast(n, times-1);
    else
        return false;
    return false;
}

int main()
{
    if(fast(13, 5))
        std::cout<<"is prime"<<std::endl;
    else
        std::cout<<"not prime"<<std::endl;
    return 0;
}