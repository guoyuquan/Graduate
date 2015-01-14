#include "friends.h"
#include <iostream>

void Friends::update_vec(std::vector<f_info> tvec)
{
    ava=0;
    fvec=tvec;
    ava=1;
}

int Friends::search_vec(const std::string & account, f_info * fin)
{
    if(ava==0)
        return -1;
    for(int i=0; i<fvec.size(); i++)
    {
        if(fvec[i].account==account)
        {
            if(fin==NULL)
                return 1;
            fin->account=fvec[i].account;
            fin->ip=fvec[i].ip;
            fin->flag=1;
            return 1;
        }
    }
    return 0;
}

void Friends::list_all()
{
    if(fvec.size()==0)
    {
        std::cout<<"none"<<std::endl;
        return;
    }
    for(int i=0; i<fvec.size(); i++)
        std::cout<<fvec[i].account<<std::endl;
}

