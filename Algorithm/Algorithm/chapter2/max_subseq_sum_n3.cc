#include<iostream>

template<typename T>
T max_sub_sum(T *a, int n);

int main()
{
    int a[]={-1, 10, -20, 101, 11, 12};
    std::cout<<max_sub_sum(a, 6)<<std::endl;
}

template <typename T>
T max_sub_sum(T *a, int n)
{
    T sum=0.0, temp=0;
    for(int i=0; i<n; i++)
        for(int j=i; j<n; j++)
        {
            sum=0;
            for(int k=i; k<=j; k++)
                sum+=*(a+k);
            if(sum>temp)
                temp=sum;
        }
    return temp;
}