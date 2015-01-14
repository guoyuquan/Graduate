#include<iostream>

template <typename T>
T majority(T *a, int n);

int main()
{
    int a[]={2, 1, 2};
    std::cout<<majority(a, 3)<<std::endl;
    int b[]={2, 1, 2, 2};
    std::cout<<majority(b, 4)<<std::endl;
    return 0;
}

template <typename T>
T majority(T *a, int n)
{
    if(n<=1)
        return *a;
    T *tar=new T[(n+1)/2];
    int i, k=0;
    for(i=0; i<n-1; i+=2)
        if(*(a+i)==*(a+i+1))
        {
            *(tar+k)=*(a+i);
            k++;
        }
    if(i==n-1)
    {
        if(*(a+i)==*(a+i-1)||*(a+i)==*(a+i-2))
        {
           *(tar+k)=*(a+i);
            k++;
        }
    }
    int can=majority(tar, k);
    delete [] tar;
    return can;
}
