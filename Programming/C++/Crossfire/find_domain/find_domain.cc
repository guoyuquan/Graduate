#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

int main()
{
    ifstream ifs1("web_do.txt");
    if(!ifs1.is_open())
    {
        cout<<"faile to open web_do"<<endl;
        return 0;
    }
    vector<string> svec1;
    string str;
    while(getline(ifs1,str))
    {
        svec1.push_back(str);
    }
    ifs1.close();
    ifstream ifs("web_domain.txt");
    if(!ifs.is_open())
    {
        cout<<"faile to open web_domain"<<endl;
        return 0;
    }
    vector<string> svec2;
    while(getline(ifs,str))
    {
        svec2.push_back(str);
    }
    ifs.close();
    for(int i=0;i!=svec1.size();++i)
    {
        svec1[i]=svec1[i].substr(7);
        svec1[i]=svec1[i].substr(0,svec1[i].size()-1);
        cout<<svec1[i]<<endl;
    }
    for(int i=0;i!=svec2.size();++i)
    {
        bool flag=false;
        for(int j=0;j!=svec1.size();++j)
        {
            if(svec1[j][0]=='w'&&svec1[j][1]=='w')
            {
                if(svec1[j].substr(4)==svec2[i])
                {
                    flag=true;
                    break;
                }
            }
            if(svec1[j][0]=='t'&&svec1[j][1]=='w'&&svec1[j][2]=='.')
            {
                if(svec1[j].substr(3)==svec2[i])
                {
                    flag=true;
                    break;
                }
            }
            if(svec1[j]==svec2[i])
            {
                flag=true;
                break;
            }
        }
        if(!flag)
        {
            svec1.push_back(svec2[i]);
        }
    }
    ofstream ofs("domain.txt");
    if(!ofs.is_open())
    {
        cout<<"faile open domain.txt"<<endl;
        return 0;
    }
    for(int i=0;i!=svec1.size();++i)
    {
        cout<<svec1[i]<<endl;
        cout<<i<<endl;
        ofs<<svec1[i]<<endl;
    }
    ofs.close();
    return 0;
}