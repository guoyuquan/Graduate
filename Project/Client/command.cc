#include "friends.h"
#include "data.h"
#include "conserv.h"
#include <sstream>

f_info curr_f;

 //to store the logged account

int proc_comm(const std::string & comm)
{
    //std::cout<<comm;
    if(comm.size()<2)
        return -1;
    if(comm[0]!='-')
    {
        if(curr_f.flag==0)
            std::cerr<<"error: choose a target with -cu command"<<std::endl;//this is a message to send to current friend;
        Records::add_rcd(curr_f.account, comm);
        return 1;
    }
    std::istringstream iss(comm);
    std::string act;
    iss>>act;
    if(act=="-add")
    {
        if(iss.eof())
            std::cerr<<"usage: -add [param]"<<std::endl;
        std::string account;
        iss>>account;
        Frd_List::fadd(account);
        //connect server, send add friend action
        Conn::adfrd(log_acc, account, 1);
    }
    else if(act=="-dl")
    {
        if(iss.eof())
            std::cerr<<"usage: -dl [param]"<<std::endl;
        std::string account;
        iss>>account;
        Frd_List::fdelete(account);
        //connect server, send delete friend action
        Conn::adfrd(log_acc, account, 0);
    }
    else if(act=="-cu")
    {
        if(iss.eof())
            std::cerr<<"usage: -cu [param]"<<std::endl;
        std::string account;
        iss>>account;
        if(friends.search_vec(account, &curr_f)<=0)
            std::cout<<account<<" is offline"<<std::endl;//change current talk friend
    }
    else if(act=="-ls")
    {
        //check all the friends
        std::vector<std::string> afvec;
        Frd_List::read(afvec);
        if(afvec.size()==0)
        {
            std::cout<<"none"<<std::endl;
            return 1;
        }
        for(int i=0; i<afvec.size(); i++)
        {
            if(friends.search_vec(afvec[i], NULL)==1)
            {
                std::string offset;
                if(afvec[i].size()<20)
                    offset=std::string(20-afvec[i].size(), ' ');
                std::cout<<afvec[i]<<offset<<": online"<<std::endl;
            }
            else
            {
                std::string offset;
                if(afvec[i].size()<20)
                    offset=std::string(20-afvec[i].size(), ' ');
                std::cout<<afvec[i]<<offset<<": offline"<<std::endl;
            }
        }
    }
    else if(act=="-ol")
    {
        friends.list_all();//list online friends
    }
    else if(act=="-rcd")
    {
        if(iss.eof())
            std::cerr<<"usage: -rcd [param]"<<std::endl;
        std::string account;
        iss>>account;
        Records::list(account);
    }
    else if(act=="-et")
    {
        Conn::log_out(log_acc);
        exit(0);
    }
    else
        std::cerr<<"error: unrecognized command"<<std::endl;
    return 1;
}