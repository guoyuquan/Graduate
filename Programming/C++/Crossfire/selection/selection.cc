#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<stdexcept>
using std::vector;
using std::string;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::endl;

int main()
{
    ifstream ifs("output.txt");
    if(!ifs.is_open())
    {
        cout<<"faile to open";
        return 0;
    }
    string line;
    int filtered=0, open=0, close=0;
    vector<std::pair<string,string> > svec;
    while(getline(ifs,line))
    {
        if(line.size()<10)
            continue;
        //cout<<"am I?"<<line<<endl;
        std::istringstream iss(line);
        string str,temp;
        iss>>temp>>str;
        temp+=str;
        //cout<<temp;
        if(temp=="Nmapscan")
        {
            //cout<<line<<endl;
            string line1, line2, line3;
            getline(ifs,line1);
            getline(ifs,line2);
            getline(ifs,line3);
            if(line1.substr(0,10)=="Host is up")
            {
                std::istringstream istr(line3);
                string str1, flag;
                istr>>str1;
                istr>>flag;
                //cout<<str1<<"**********"<<endl;
                //istr>>str1;
                if(flag=="open")
                {
                    string ip, domain;
                    std::pair<string, string> ipair;
                    ++open;
                    iss>>str;
                    iss>>str;
                    //cout<<str<<"******"<<endl;
                    iss>>ip;
                    if(iss>>domain)
                    {
                        //cout<<"IP: "<<temp<<"domain name:"<<temp<<endl;
                        ipair=std::make_pair(ip,domain);
                        svec.push_back(ipair);
                        continue;
                    }
                    else
                    {
                        ipair=std::make_pair("none",ip);
                        svec.push_back(ipair);
                    }
                }
                else if(str1=="filtered")
                {
                    ++filtered;
                }
                else
                {
                    ++close;
                }
            }
        }
    }
    ifs.close();
    ofstream ofs("input.txt");
    if(!ofs.is_open())
    {
        cout<<"faile to open"<<endl;
    }
    string curr="",temp;
    int j=0;
    for(int i=0;i!=svec.size();++i)
    {
        if(svec[i].first=="none")
        {
            ofs<<svec[i].second<<endl;
            ++j;
        }
        else
        {
            if(svec[i].first!=curr)
            {
                ++j;
                curr=svec[i].first;
                cout<<svec[i].second<<endl;
                temp=svec[i].second.substr(1,svec[i].second.size()-2);
                cout<<temp<<endl;
                ofs<<temp<<endl;
            }
        }
    }
    cout<<"open:"<<open<<endl;
    cout<<"filtered:"<<filtered<<endl;
    cout<<"close:"<<close<<endl;
    return 0;
}