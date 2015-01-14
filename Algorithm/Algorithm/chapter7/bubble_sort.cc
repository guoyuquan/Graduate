#include<iostream>

template <typename T>
void bubble_sort(T *a, int n);

int main()
{
    int a[]={9,8,7,6,5,4,3,2,1,0};
    bubble_sort(a, 10);
    for(int i=0; i<10; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    return 0;
}

template <typename T>
void bubble_sort(T *a, int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=n-1; j>=i; j--)
            if(a[j]<a[i])
                std::swap(a[j], a[i]);
        //for(int k=0; k<n; k++)
          //  std::cout<<a[k]<<" ";
        //std::cout<<std::endl;
    }
}