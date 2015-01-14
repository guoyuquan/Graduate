#include<iostream>

double fun_h(double a, double b, int n)
{
    return (a-b)/n;
}

double fun_y(double a, double b, int k, int n)
{
    return a+k*fun_h(a, b, n);
}

double cube(int a, int b, int n)
{
    if(n<=0)
    {
        std::cout<<"bad divisor"<<std::endl;
        return 0;
    }
    if(b<a)
        return 0;
    double sum=fun_y(a, b, 0, n);
    for(int i=1; i<n; i++)
    {
        int params;
        if(i%2==0)
            params=2;
        else
            params=4;
        sum+=params*fun_y(a, b, i, n);
    }
    return fun_h(a, b, n)*sum;
}

int main()
{
    std::cout<<cube(0, 1, 100)<<std::endl;
    std::cout<<cube(0, 1, 100000000)<<std::endl;
    return 0;
}