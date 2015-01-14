#include<iostream>

int pascal(int n)
{
    if(n<4)
        return 1;
    int sum=0;
    int i;
    for(i=1; i<n; i++)
    {
        sum+=i;
        if(n<=sum)
            break;
    }
    if(n==sum||n==sum-i+1)
        return 1;
    std::cout<<n<<std::endl;
    return pascal(n-i) + pascal(n-i+1);
}

int main()
{
    //for(int i=0; i<100; i++)
        std::cout<<pascal(700)<<std::endl;
    return 0;
}

