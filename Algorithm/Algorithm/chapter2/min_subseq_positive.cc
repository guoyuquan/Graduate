#include<iostream>

template <typename T>
T min_positive(T *a, int n);

int main()
{
    int a[]={-1, 10, -20, 12, 11, 12};
    std::cout<<min_positive(a, 6)<<std::endl;
    return 0;
}

template <typename T>
T min_positive(T *a, int n)
{
    T sum=0, temp=0;
    bool flag=true;
    for(int i=0; i<n; i++)
    {
        temp=0;
        for(int j=i; j<n; j++)
        {
            temp+=*(a+j);
            if(flag&&temp>0)
            {
                sum=temp;
                flag=false;
            }
            if(temp>0&&sum>temp)
                sum=temp;
            if(temp>0&&j<n-1&&*(a+j+1)>0)
                temp=0;
        }
    }
            
    return sum;
}