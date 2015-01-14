#include <iostream>

void swap(int &a, int &b);

int removeElement(int A[], int n, int elem) {
    int total=0;
    int backindex=n-1;
    for(int i=0; i<backindex;i++ )
    {
        if(A[i]==elem)
        {
            while(backindex>=0&&A[backindex]==elem)
            {
                backindex--;
            }
            if(backindex>=0)
            {
                swap(A[backindex], A[i]);
                total++;
                continue;
            }
            break;
        }
    }
    return total;
}
void swap(int &a, int &b)
{
    int temp=a;
    a=b;
    b=temp;
}

int main()
{
    int a[2]={4,5};
    std::cout<<removeElement(a, 2, 4)<<std::endl;
    return 0;
}