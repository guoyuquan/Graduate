#include<iostream>

template <typename T>
T max_sub_sum(T *a, int n);

int main()
{
    int a[]={-1, 10, -20, 101, 11, 12};
    std::cout<<max_sub_sum(a, 6)<<std::endl;
    return 0;
}

template <typename T>
T max_sub_sum(T *a, int n)
{
    T sum=0, temp=0;
    for(int i=0; i<n; i++)
    {
        temp+=*(a+i);
        if(temp>sum)
            sum=temp;
        if(temp<0)
        {
            temp=0;
        }
    }
    return sum;
}