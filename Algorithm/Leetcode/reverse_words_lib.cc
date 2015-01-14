#include<iostream>
#include<sstream>
#include<vector>

void reverse_word(std::string &s)
{
    std::istringstream iss(s);
    std::string str;
    std::vector<std::string> svec;
    while(iss>>str)
    {
        svec.push_back(str);
    }
    s.clear();
    for(int i=svec.size()-1; i>0; --i)
        s+=svec[i]+" ";
    if(svec.size()>0)
        s+=svec[0];
}

int main()
{
    std::string str="the sky is blue";
    reverse_word(str);
    std::cout<<str<<std::endl;
    return 0;
}