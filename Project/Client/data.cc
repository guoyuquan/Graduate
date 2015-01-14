#include "data.h"
#include <fstream>
#include <time.h>

void Records::add_rcd(const std::string & account, const std::string & msg)
{
    std::string filename="data/";
    filename+=account;
    std::ofstream ofs(filename, std::fstream::app);
    if(!ofs.is_open())
        return;
    time_t ttime;
    time(&ttime);
    std::string tt=ctime(&ttime);
    for(int i=0; i<tt.size();++i)
        if(tt[i]==' ')
            tt[i]=',';
    ofs<<tt<<std::endl;
    ofs<<msg<<std::endl;
    ofs.close();
}

void Records::list(const std::string &account)
{
    std::string filename="data/";
    filename+=account;
    std::ifstream ifs(filename);
    if(!ifs.is_open())
        return;
    std::string record;
    while(ifs>>record)
        std::cout<<record<<std::endl;
    ifs.close();
}

int Frd_List::read(std::vector<std::string> &vec)
{
    std::ifstream ifs("data/friends");
    if(!ifs.is_open())
    {
        return -1;
    }
    std::string account;
    while(ifs>>account)
    {
        //std::cout<<account<<std::endl;
        vec.push_back(account);
    }
    ifs.close();
    return 1;
}

int Frd_List::fadd(const std::string & account)
{
    std::ofstream ofs("data/friends", std::fstream::app);
    if(!ofs.is_open())
        return -1;
    ofs<<account<<std::endl;
    ofs.close();
    return 1;
}

int Frd_List::fdelete(const std::string & account)
{
    std::ifstream ifs("data/friends");
    if(!ifs.is_open())
        return -1;
    std::string acc;
    std::vector<std::string> acc_vec;
    while(ifs>>acc)
    {
        if(acc==account)
            continue;
        acc_vec.push_back(acc);
    }
    ifs.close();
    std::ofstream ofs("data/friends");
    if(!ofs.is_open())
        return -1;
    for(int i=0; i<acc_vec.size(); ++i)
    {
        ofs<<acc_vec[i]<<std::endl;
    }
    ofs.close();
    return 1;
}