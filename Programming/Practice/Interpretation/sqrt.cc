#include<iostream>

double sqrt(int n)
{
    double temp=0.0, div=n/2;
    double var=0.0, curr=0.0;
    for(int i=0; true; i++)
    {
        temp=n/div;
        div=(temp+div)/2;
        std::cout<<div<<" ";
        var=curr-div;
        curr=div;
        if(var<0)
            if(-var/div<=0.0001)
                break;
        if(var>=0)
            if(var/div<=0.0001)
                break;
    }
    std::cout<<std::endl;
    return div;
}

int main()
{
    std::cout<<sqrt(10000)<<std::endl;
    return 0;
}