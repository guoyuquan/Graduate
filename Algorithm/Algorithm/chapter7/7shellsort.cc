#include<iostream>

template<typename T>
void shell(T *a, int n)
{
    static int inc[3]={1,3,7};
    for(int i=2; i>=0; i--)
    {
        for(int j=inc[i]; j<n; j++)
        {
            T temp=a[j];
            int k=j;
            for(; k>inc[i]-1; k-=inc[i])
                if(a[k]<a[k-inc[i]])
                    a[k]=a[k-inc[i]];
                else break;
            a[k]=temp;
        }
        for(int f=0; f<n; f++)
            std::cout<<a[f]<<" ";
        std::cout<<std::endl;
    }
}

int main()
{
    int a[]={9,8,7,6,5,4,3,2,1};
    shell(a, 9);
    for(int i=0; i<9; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    return 0;
}