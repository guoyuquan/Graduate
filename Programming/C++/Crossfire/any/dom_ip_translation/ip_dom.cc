#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
using std::cout;
using std::vector;
using std::endl;
using std::string;
using std::pair;

int main()
{
    vector<pair<string, vector<string> > > dom_vec;
    vector<string> svec;
    vector<pair<string, string> > result;
    std::ifstream ifs("ip_.txt");
    if(!ifs.is_open())
    {
        cout<<"fail open ip_.txt"<<endl;
        return 0;
    }
    string str;
    while(getline(ifs, str))
    {
        svec.push_back(str);
    }
    ifs.close();
    ifs.open("domain_ip.txt");
    if(!ifs.is_open())
    {
        cout<<"fail open domain_ip"<<endl;
        return 0;
    }
    while(getline(ifs, str))
    {
        string domain;
        string ip;
        vector<string> ipvec;
        std::istringstream iss(str);
        iss>>domain;
        while(iss>>ip)
        {
            ipvec.push_back(ip);
        }
        dom_vec.push_back(std::make_pair(domain, ipvec));
        ip.clear();
    }
    ifs.close();
    for(int i=0; i!=svec.size(); ++i)
    {
        for(int j=0; j!=dom_vec.size(); ++j)
        {
            for(int k=0; k!=dom_vec[j].second.size(); ++k)
                if(svec[i]==dom_vec[j].second[k])
                    result.push_back(std::make_pair(svec[i], dom_vec[j].first));
        }
    }
    std::ofstream ofs("ip_dom.txt");
    if(!ofs.is_open())
    {
        cout<<"fail open ip_dom"<<endl;
        return 0;
    }
    for(int i=0; i!=result.size(); ++i)
    {
        cout<<result[i].first<<" "<<result[i].second<<endl;
        ofs<<result[i].first<<" "<<result[i].second<<endl;
    }
    ofs.close();
    return 0;
}



