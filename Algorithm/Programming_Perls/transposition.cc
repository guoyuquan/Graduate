#include <iostream>

void trans1(int a[], int i, int n);
void trans2(int a[], int i, int n);
int main()
{
    int a[11]={0,1,2,3,4,5,6,7,8,9,10};
    trans2(a, 3, 11);
    for(int i=0; i<11; i++)
        std::cout<<a[i]<<" ";
    std::cout<<std::endl;
}

void trans1(int a[], int offset, int n)
{
    for(int i=0; i<offset; i++)
    {
        int t=a[i];
        int j=i;
        for(; j<n;j+=offset)
        {
            a[j]=a[j+offset];
        }
        a[j]=t;
    }
}

void reverse(int a[], int start, int end)
{
    while(start<end)
    {
        int t=a[start];
        a[start]=a[end];
        a[end]=t;
        start++;
        end--;
    }
}
void trans2(int a[], int offset, int n)
{
    reverse(a, 0, offset-1);
    reverse(a, offset, n-1);
    reverse(a, 0, n-1);
}