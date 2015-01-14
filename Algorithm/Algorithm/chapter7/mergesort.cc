#include<iostream>

template<typename T>
void mergesort(T *a, int n);

int main()
{
    int a[]={1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 8, 16};
    mergesort(a, 16);
    for(int i=0; i<16; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
   // std::cout<<what<<std::endl;
    return 0;
}

template<typename T>
void merge(T *a, T *tar, int left, int center, int right)
{
    int left_end=center-1;
    int tmp=left, ls=left, rs=center;
    while(ls<=left_end&&rs<=right)
    {
        if(a[ls]<a[rs])
            tar[tmp++]=a[ls++];
        else
            tar[tmp++]=a[rs++];
    }
    while(rs<=right)
        tar[tmp++]=a[rs++];
    while(ls<=left_end)
        tar[tmp++]=a[ls++];
    for(;left<=right; left++)
        a[left]=tar[left];
}

template<typename T>
void m_sort(T *a, T *tar, int left, int right)
{
    if(left<right)
    {
        int center=(left+right)/2;
        m_sort(a, tar, left, center);
        m_sort(a, tar, center+1, right);
        merge(a, tar, left, center+1, right);
    }
}

template<typename T>
void mergesort(T *a, int n)
{
    if(n<=1)
        return;
    T *tar=new T[n];
    m_sort(a, tar, 0, n-1);
    delete [] tar;
}
