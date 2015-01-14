#include<iostream>

template<typename T>
void shellsort(T *a, int);

int main()
{
    int a[]={1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 8, 16};
    shellsort(a, 16);
    for(int i=0; i<16; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    return 0;
}

template<typename T>
void shellsort(T *a, int n)
{
    for(int inc=n/2; inc>0; inc/=2)
    {
        for(int i=inc-1; i<n; i++)
        {
            T temp=a[i];
            int j=i;
            for(; j>=inc; j-=inc)
            {
                if(temp<a[j-inc])
                    a[j]=a[j-inc];
                else
                    break;
            }
            std::cout<<"******"<<inc<<"*******"<<std::endl;
           for(int k=0; k<n; k++)
                std::cout<<a[k]<<" ";
            std::cout<<std::endl;
            a[j]=temp;
        }
    }
}