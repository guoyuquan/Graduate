#include"balance.h"

int main()
{
    Binary<int> tree;
    int a[]={9,1,3,2,4,7,6,5,8,0};
    for(int i=0; i<10; i++)
        tree.insert(a[i]);
    tree.print();
    return 0;
}