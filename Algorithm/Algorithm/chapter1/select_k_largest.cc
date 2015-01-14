#include<iostream>

template<typename T>
void quick_sort(T *, int size);

int main()
{
    int a[]={0,6,2,4,1,3,5,9,8,7};
    quick_sort(a, 10);
    for(int i=0;i<10; ++i)
        std::cout<<a[i]<<" ";
    std::cout<<a[5]<<std::endl;
    return 0;
}

template<typename T>
void quick_sort(T *array, int size)
{
    if(size<=1)
        return;
    std::swap(array[size/2], array[0]);
    int pivot=0;
    int i=size-1;
    while(pivot!=i)
    {
        if(array[i]<array[pivot])
        {
            std::swap(array[i], array[pivot+1]);
            std::swap(array[pivot], array[pivot+1]);
            pivot++;
        }
        else
            i--;
    }
    quick_sort(array, pivot-1);
    quick_sort(array+pivot+1, size-pivot-1);
}