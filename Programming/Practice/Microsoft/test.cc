#include <iostream>
#include <string>

using namespace std;

void CMD1(string &str, int x, int i, int j)
{
    for(; i<=j; i++)
    {
        str[i]=x;
        //std::cout<<i<<j<<std::endl;
    }
    //std::cout<<str<<std::endl;
}

char func(int ch, int k)
{
    int s=ch-'A';
    s=s+k;
    char t=s%26;
    return 'A'+t;
}

void CMD2(string &str, int i, int j, int k)
{
    for(; i<=j; i++)
    {
        //std::cout<<i<<std::endl;
        str[i]=func(str[i], k);
        
    }
}

void CMD3(string &str, int i)
{
    if(i>=str.size())
        return;
    string ret=str.substr(i);
    ret+=str.substr(0, i);
    str=ret;
    //std::cout<<str<<std::endl;
    //std::cout<<"111"<<std::endl;
}

void CMD4(string &str, int i, int j)
{
    if(i>j)
        return;
    CMD4(str, i+1, j);
    CMD2(str, i, j, 1);
    //std::cout<<str<<std::endl;
    //std::cout<<"111"<<std::endl;
}


int main()
{
    //std::cout<<func('Z', 26);
    int len, row;
    int i, j, k, m;
    char ch;
    string str, temp;
    std::cin>>len>>row>>str;
    //std::cout<<std::endl;
    //std::cout<<str<<std::endl;
    for(int z=0; z<row; z++)
    {
        if(z==0)
        {
            std::cin>>temp>>m>>i>>j>>ch;
            CMD1(str, ch, i, j);
        }
        if(z==1)
        {
            std::cin>>temp>>m>>i>>j>>k;
            CMD2(str, i, j, k);
        }
        if(z==2)
        {
            std::cin>>temp>>m>>i;
            CMD3(str,i);
        }
        if(z==4)
        {
            std::cin>>temp>>m>>i>>j;
            CMD4(str, i, j);
        }
    }
    std::cout<<str<<std::endl;
}