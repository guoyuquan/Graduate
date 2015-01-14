#include <iostream>
#include <stdlib.h>
#include <assert.h>

int binary_search(int a[], int target, int n)
{
    int cnt=0;
    int low=0, high=n-1, mid=n/2;
    for(int i=0; low<=high; i++)
    {
        if(a[mid]>target)
        {
            high=mid-1;
            mid=(low+high)/2;
            cnt++;
        }
        else if(a[mid]<target)
        {
            low=mid+1;
            mid=(low+high)/2;
            cnt++;
        }
        else
        {
            assert(a[mid]==target);
            //std::cout<<cnt<<" times"<<std::endl;
            return mid;
        }
    }
    std::cout<<cnt<<" times"<<std::endl;
    return -1;
}

int main()
{
    int a[11]={0,1,2,3,4,5,6,7,8,9,10};
    clock_t start=clock();
    for(int i=0; i<11; i++)
    {
        std::cout<<binary_search(a, i, 11);
        std::cout<<" ";
    }
    clock_t t=clock()-start;
    std::cout<<t<<"miliseconds"<<std::endl;
    std::cout<<std::endl;
    return 0;
}