#include<iostream>
#include<vector>

void reverse_word(std::string &s);

int main()
{
    std::string str="the sky is blue";
    reverse_word(str);
    std::cout<<str<<std::endl;
    return 0;
}

void reverse_word(std::string &s)
{
    bool lflag=false, rflag=false;
    for(int i=0,j=s.size()-1, lsize=0, rsize=0; i<=j; i++, j--)
    {
        std::cout<<s<<std::endl;
        std::swap(s[i],s[j]);
        if(s[i]==' ')
        {
            for(int l=i-lsize, r=i-1;l<r; l++, r--)
                std::swap(s[r], s[l]);
            lsize=0;
        }
        else
            lsize++;
        if(s[j]==' ')
        {
            for(int l=j+1, r=j+rsize; l<r; l++, r--)
                std::swap(s[r], s[l]);
            rsize=0;
        }
        else
            rsize++;
    }
}