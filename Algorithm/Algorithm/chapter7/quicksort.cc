#include<iostream>

template<typename T>
void quicksort(T *a, int n);

int main()
{
    int a[]={1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 16, 7, 15, 8, 16};
    quicksort(a, 16);
    for(int i=0; i<16; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    return 0;
}

template<typename T>
void quicksort(T *a, int n)
{
    if(n<=1)
        return;
    std::swap(a[0], a[n/2]);
    int pivot=0;
    for(int i=n-1; i>pivot;)
    {
        if(a[i]<a[pivot])
        {
            std::swap(a[i], a[pivot+1]);
            std::swap(a[pivot+1], a[pivot]);
            pivot++;
            continue;
        }
        i--;
    }
    quicksort(a, pivot);
    quicksort(a+pivot+1,n-pivot-1);
}