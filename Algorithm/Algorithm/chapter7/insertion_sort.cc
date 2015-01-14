#include<iostream>

template <typename T>
void insertion_sort(T *a, int n)
{
    for(int i=1; i<n; i++)
    {
        T temp=a[i];
        int j=i-1;
        for(; j>=0&&a[j]>temp; j--)
            a[j+1]=a[j];
        /*for(int k=0; k<n; k++)
            std::cout<<a[k]<<" ";
        std::cout<<std::endl;*/
        a[++j]=temp;
    }
}

int main()
{
    int a[]={9,8,7,6,5,4,3,2,1,0};
    insertion_sort(a, 10);
    for(int i=0; i<10; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    return 0;
}