#include <iostream>

void insertionsort1(int a[], int n)
{
    for(int i=1; i<n; i++)
        for(int j=i; j>=1; j--)
        {
            if(a[j-1]>a[j])
                std::swap(a[j-1], a[j]);
        }
}

void insertionsort2(int a[], int n)
{
    for(int i=1; i<n; i++)
    {
        int t=a[i];
        int j=i;
        for(; j>=1&&a[j-1]>t; j--)
            a[j]=a[j-1];
        a[j]=t;
    }
}


int main()
{
    int a[10]={9,8,7,6,5,4,3,2,1,0};
    clock_t start=clock();
    insertionsort1(a, 10);
    clock_t end=clock();
    std::cout<<end-start<<std::endl;
    int b[10]={9,8,7,6,5,4,3,2,1,0};
    start=clock();
    insertionsort2(b, 10);
    end=clock();
    std::cout<<end-start<<std::endl;
    for(int i=0; i<10; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    for(int i=0; i<10; i++)
        std::cout<<b[i]<<" ";
    std::cout<<std::endl;
    return 0;
}