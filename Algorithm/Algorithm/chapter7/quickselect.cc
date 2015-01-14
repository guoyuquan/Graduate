#include<iostream>

template<typename T>
T quickselect(T *a, int k, int n);

int main()
{
    int a[]={1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 16, 7, 15, 8, 16};
    std::cout<<quickselect(a, 5, 16)<<std::endl;
    return 0;
}

template<typename T>
T quickselect(T *a, int k, int n)
{
    if(n<=1)
        return a[0];
    std::swap(a[0], a[n/2]);
    int pivot=0;
    for(int i=n-1; i>pivot;)
    {
        if(a[i]<=a[pivot])
        {
            std::swap(a[i], a[pivot+1]);
            std::swap(a[pivot], a[pivot+1]);
            pivot++;
            continue;
        }
        i--;
    }
    if(k<pivot+1)
        return quickselect(a, k, pivot);
    else if(k>pivot+1)
        return quickselect(a+pivot+1, k-pivot-1, n-pivot); 
    else
        return a[pivot];
}