#include<iostream>

int func(int n)
{
    if(n<3)
        return n;
    int n_1=2, n_2=1, n_3=0;
    int sum=0;
    for(int i=3; i<=n; i++)
    {
        sum=n_1+2*n_2+3*n_3;
        n_3=n_2;
        n_2=n_1;
        n_1=sum;
        //std::cout<<sum<<std::endl;
    }
    return sum;
}

int main()
{
    std::cout<<func(10)<<std::endl;
    return 0;
}