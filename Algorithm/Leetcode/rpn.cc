#include<iostream>
#include<vector>

int main()
{
    using std::string;
    std::string str;
    std::vector<string> svec;
    while(std::cin>>str)
        svec.push_back(str);
    if(svec.size()==1)
    {
        std::cout<<stoi(svec[0])<<std::endl;
        return 0;
    }
    if(svec.size()==0)
        return 0;
    std::vector<string>::iterator it=svec.begin();
    int tmp;
    while(svec.size()!=1)
    {
        std::vector<string>::iterator begin=svec.begin();
    for(;(begin+2)!=svec.end()&&begin!=svec.end();++begin)
    {
        if(*(begin+2)=="+"||*(begin+2)=="-"||*(begin+2)=="*"||*(begin+2)=="/")
        {
            if(*(begin+2)=="+")
                tmp=stoi(*begin)+stoi(*(begin+1));
            else if(*(begin+2)=="-")
                tmp=stoi(*begin)-stoi(*(begin+1));
            else if(*(begin+2)=="*")
                tmp=stoi(*begin)*stoi(*(begin+1));
            else
            {
                if(stoi(*(begin+1))!=0)
                    tmp=stoi(*begin)/stoi(*(begin+1));
                else
                {
                    std::cerr<<"error input: 0 cannot be the divider"<<std::endl;
                    exit(0);
                }
            }
            begin=svec.erase(begin);
            begin=svec.erase(begin);
            *begin=std::to_string(tmp);
            break;
        }
    }
        
    }
    
    std::cout<<tmp<<std::endl;
    return 0;
}