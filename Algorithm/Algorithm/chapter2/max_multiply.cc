#include<iostream>

int multiply(int *a, int n);

int main()
{
    int a[]={-1, 10, -20, 101, 11, 12};
    std::cout<<multiply(a, 6)<<std::endl;
    return 0;
}

int multiply(int *a, int n)
{
    int cnt=0,sum=1, sum2=1;
    int first=0, last=0;
    for(int i=0; i<n; i++) 
        if(*(a+i)<0)
        {
            cnt++;
            if(first==last&&first==0)
                first=i;
            else
                last=i;
        }
    if(cnt%2==0)
        for(int i=0; i<n; i++)
        {
            sum*=*(a+i);
        }
    else
        for(int i=0; i<n; i++)
        {
            if(i<last)
                sum*=*(a+i);
            if(i>first)
                sum2*=*(a+i);
        }
    return sum>sum2?sum:sum2;
}