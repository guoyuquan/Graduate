#include<iostream>
#include<vector>

template<typename T>
T max_positive_sub(T *a, int n);

int main()
{
    int a[]={-1, 10, -20, 101, 11, 12};
    std::cout<<max_positive_sub(a, 6)<<std::endl;
    return 0;
}

void quick_sort(std::pair<int, int> *p, int n)
{
    if(n<1)
        return;
    if(p[0].second>p[n/2].second)
        std::swap(p[0], p[n/2]);
    int pivot=0, i=n-1;
    while(pivot<=i)
    {
        if(p[i].second<p[pivot].second)
        {
            std::swap(p[i],p[pivot+1]);
            std::swap(p[pivot], p[pivot+1]);
            pivot++;
        }
        else i--;
    }
    quick_sort(p,pivot-1);
    quick_sort(p+pivot+1, n-pivot-1);
}

template<typename T>
T max_positive_sub(T *a, int n)
{
    std::pair<int, int> *arr = new std::pair<int, int> [n];
    T sum=0;
    for(int i=0; i<n; i++)
    {
        sum+=*(a+i);
        arr[i]=std::make_pair(i, sum);
    }
    quick_sort(arr, n);
    sum=0;
    bool flag=true;
    int temp=0;
    for(int i=0; i<n-1; i++)
    {
        if(arr[i].first<arr[i+1].first)
        {
            temp=arr[i+1].second-arr[i].second;
            if(temp>arr[i+1].second&&arr[i+1].second>0)
                temp=arr[i+1].second;
            if(temp>arr[i].second&&arr[i].second>0)
                temp=arr[i].second;
        }
        //std::cout<<temp<<std::endl;
        if(temp>0&&flag)
        {
            sum=temp;
            flag=false;
        }
        if(temp>0&&temp<sum)
            sum=temp;
    }
    delete[] arr;
    return sum;
}