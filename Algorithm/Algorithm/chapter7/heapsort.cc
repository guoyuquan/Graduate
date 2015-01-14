#include<iostream>

template <typename T>
void heapsort(T *a, int);

int main()
{
    int a[]={1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 8, 16,};
    heapsort(a, 16);
    for(int i=0; i<16; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    return 0;
}

template <typename T>
void siftdown(T *a, int index, int n)
{
    T temp=a[index-1];
    while(index*2<=n)
    {
        if(index*2==n)
        {
            if(a[index-1]>a[index*2-1])
                std::swap(a[index-1], a[index*2-1]);
            break;
        }
        if(a[index*2]>a[index*2-1])
        {
            if(temp>a[index*2-1])
                std::swap(a[index-1], a[index*2-1]);
            else
                break;
            index*=2;
        }
        else
        {
            if(temp>a[index*2])
                std::swap(a[index-1], a[index*2]);
            else
                break;
            index=2*index+1;
        }
    }
}

template <typename T>
void build_heap(T *a, int n)
{
    for(int i=n/2; i>=1; i--)
        siftdown(a,i,n);
}

template <typename T>
void delete_min(T * a, int n)
{
    std::swap(a[0], a[n-1]);
    siftdown(a, 1, n-1);
}

template<typename T>
void heapsort(T *a, int n)
{
    build_heap(a, n);
    std::cout<<std::endl;
    for(int i=n; i>0; i--)
    {
        delete_min(a, i);
        for(int j=0;j<n;j++)
            std::cout<<a[j]<<" ";
        std::cout<<std::endl;
    }
}

