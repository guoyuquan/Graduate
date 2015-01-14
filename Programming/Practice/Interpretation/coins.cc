#include<iostream>

int first(int kinds)
{
    if(kinds>5)
    {
        std::cout<<"error:out of band"<<std::endl;
        exit(1);
    }
    static int a[5]={1,5,10,25,50};
    return a[kinds-1];
}

int cc(int amount, int kinds)
{
    if(amount==0)
        return 1;
    if(amount<0||kinds==0)
        return 0;
    else
    {
        return  cc(amount, kinds-1)+cc(amount-first(kinds), kinds);
    }
}
int change(int amount)
{
   return cc(amount, 5);
}
int main()
{
    std::cout<<change(100)<<std::endl;
}