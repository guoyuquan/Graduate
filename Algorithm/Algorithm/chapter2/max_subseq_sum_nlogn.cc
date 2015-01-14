#include<iostream>

template <typename T>
T max_sum(T *a, int n);

template <typename T>
T max_sub_sum(T *a, int left, int right);

int main()
{
    int a[]={-1, 10, -20, 101, 11, 12};
    std::cout<<max_sum(a, 6)<<std::endl;
    return 0;
}

template <typename T>
T max_sum(T *a, int n)
{
    return max_sub_sum(a, 0, n-1);
}

template <typename T>
T max_sub_sum(T *a, int left, int right)
{
    if(left==right)
    {
        if(a[left]>0)
            return a[left];
        else 
            return 0;
    }
    int center=(left+right)/2;
    int max_left_sum=max_sub_sum(a, left, center);
    int max_right_sum=max_sub_sum(a, center+1, right);
    int left_border_sum=0, max_left_border_sum=0;
    for(int i=center; i>=left; i--)
    {
        left_border_sum+=a[i];
        if(max_left_border_sum<left_border_sum)
            max_left_border_sum=left_border_sum;
    }
    int max_right_border_sum=0, right_border_sum=0;
    for(int i=center+1;i<=right; i++)
    {
        right_border_sum+=a[i];
        if(right_border_sum>max_right_border_sum)
            max_right_border_sum=right_border_sum;
    }
    return std::max(std::max(max_left_sum, max_right_sum), max_left_border_sum+max_right_border_sum);
}