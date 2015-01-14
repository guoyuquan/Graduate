#include <iostream>

void quicksort(int a[], int low, int high)
{
    if(low>=high)
        return;
    int mid=(low+high)/2;
    std::swap(a[low], a[mid]);
    mid=low;
    for(int i=high-1; i>mid; i--)
    {
        if(a[i]<a[mid])
        {
            std::swap(a[mid+1], a[i]);
            std::swap(a[mid], a[mid+1]);
            mid++;
            i++;
        }
    }
    for(int i=low; i<high; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    quicksort(a+low, 0, mid);
    quicksort(a+mid+1, 0, high-mid-1);
}

int main()
{
    int a[10]={9,8,7,6,5,4,3,2,1,0};
    quicksort(a, 0, 10);
    for(int i=0; i<10; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    return 0;
}