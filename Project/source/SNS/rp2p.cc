#include <iostream>
#include <sstream>
#include <time.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include "neo4j.h"
#include "userdb.h"
#include "rp2p.h"

class Sock
{
public:
    Sock(int i):sock(i){}
    int send_msg(const std::string &);
    ~Sock();
private:
    int sock;
    int valid;
};

Sock::~Sock()
{
    close(sock);
}

int Sock::send_msg(const std::string &msg)
{
    struct rp2p rpp;
    char buf[1500];
    memset(buf, 0, 1500);
    memcpy(buf, &rpp, sizeof(rpp));
    memcpy(buf+sizeof(rpp), msg.c_str(), msg.size());
    send(sock, buf, sizeof(rpp)+msg.size(), 0);
    return 1;
}

/*
 * sign_on function used for process user register process
 */
int Action::sign_on(const char * msg)
{
    string smsg(msg);
    string account, password, ip;
    std::istringstream iss(smsg);
    iss>>account>>password>>ip;
    account = account.substr(8);
    DBConn dbconn;
    if(dbconn.query_pwd(account)!="")
        return -1; //-1 stand for the account already exist;
    password = password.substr(9);
    if(dbconn.insert(account, password)==-1)
        return -2; //-2 stand for mysql database error
    if(U_NeoDB::create_account(account)==-1)
        return -3; //-3 stand for neo4j database error
    ip=ip.substr(3);
    string xml;
    if(get_ip_location(ip, xml)==1)
        ip=xml; //-6 stand for ip translation error
    else
        ip="unknown";
    if(U_NeoDB::set_freq_location(account, ip)==-1)
        return -6; //-6 stand for neo4j update location error
    //std::cout<<account<<"  "<<password<<"  "<<ip<<std::endl;
    //std::cout<<ip<<std::endl;
    return 1;
}

/*
 * login function is in charge of process login process
 */
int Action::login(const char * msg, string &fip)
{
    string smsg(msg);
    std::istringstream iss(smsg);
    string account, pwd, client, ip;
    iss>>account>>pwd>>client>>ip;
    account=account.substr(8);
    pwd=pwd.substr(9);
    DBConn dbconn;
    if(dbconn.query_pwd(account)!=pwd)
        return -1; //-1 stand for pwd error;
    if(U_NeoDB::login(account, 1)==-1)
        return -2; //-2 stand for neo db error;
    client=client.substr(7);
    if(U_NeoDB::set_client(account, client)==-1)
        return -3; //-3 stand for neodb set client error;
    ip=ip.substr(3);
    if(U_NeoDB::set_ip(account, ip)==-1)
        return -5; //-5 stand for neodb set ip error;
    string xml, location;
    if(get_ip_location(ip, xml)==1)
        location=xml; //-6 stand for ip translation error
    else
        location="unknown";
    if(U_NeoDB::set_location(account, location)==-1)
        return -6; //-6 stand for set location error
    if((fip=U_NeoDB::get_all_fip(account))=="err")
        return -7; //error ip
    //std::cout<<account<<" "<<pwd<<" "<<client<<" "<<ip<<" "<<location<<" "<<fip<<std::endl;
    return 1;
}

/*
 * log_out function is responsible for clear when log_out
 */

int Action::log_out(const char * msg)
{
    string account(msg);
    account = account.substr(8);
    if(U_NeoDB::login(account, -1)==-1)
        return -2; //-2 stand for neo db error;
    time_t lttime;
    string ttime;
    if(time(&lttime)==-1)
    {
        ttime="unknown";
    }
    ttime=string(ctime(&lttime));
    for(int i=0; i<ttime.size(); i++)
        if(ttime[i]==' ')
            ttime[i]=',';
    ttime[ttime.size()-1]=0;
    if(U_NeoDB::set_last_login(account, ttime.c_str())==-1)
        return -1; //-1 stand for set time error;
    std::cout<<ttime<<" "<<account<<std::endl;
    return 1;
}


/*
 * Update class is used to update different part of the information after login
 */

class Update
{
public:
    static int upd_ip(const char *);
    static int upd_loc(const char *);
    static int upd_frd(const char *);
    static int upd_il(const char *);
    static int upd_if(const char *);
    static int upd_fl(const char *);
    static int upd_all(const char *);
    static int upd_info(const char *, string & fip);
};

int Update::upd_ip(const char * msg)
{
    std::istringstream iss(msg);
    string account, ip;
    iss>>account>>ip;
    account=account.substr(8);
    ip=ip.substr(3);
    if(U_NeoDB::set_ip("JERRY", ip)==-1)
        return -1;
    //std::cout<<account<<ip<<std::endl;
    //std::cout<<U_NeoDB::get_all_fip("123456")<<std::endl;
    return 1;
}

int Update::upd_loc(const char * msg)
{
    std::istringstream iss(msg);
    string account, ip;
    iss>>account>>ip;
    account=account.substr(8);
    ip=ip.substr(3);
    string location;
    if(get_ip_location(ip, location)!=1)
        location="unknown";
    if(U_NeoDB::set_location(account, location)==-1)
        return -1;
    //std::cout<<location<<" "<<ip<<" "<<account<<std::endl;
    return 1;
}

int Update::upd_frd(const char * msg)
{
    std::istringstream iss(msg);
    string account, adord, frd;
    iss>>account>>adord>>frd;
    account=account.substr(8);
    frd=frd.substr(7);
    if(adord=="add")
    {
        if(U_NeoDB::add_friends(account, frd)==-1)
            return -1;
    }
    else if(adord=="delete")
    {
        if(U_NeoDB::delete_friends(account, frd)==-1)
            return -2;
    }
    return 1;
}

int Update::upd_il(const char * msg)
{
    string account, ip, location;
    std::istringstream iss(msg);
    iss>>account>>ip;
    account=account.substr(8);
    ip=ip.substr(3);
    if(get_ip_location(ip, location)!=1)
        location="unknown";
    if(U_NeoDB::set_ip(account, ip)==-1)
        return -1;
    if(U_NeoDB::set_location(account, location)==-1)
        return -2;
    return 1;
}

int Update::upd_if(const char * msg)
{
    string account, ip, adord, frd;
    std::istringstream iss(msg);
    iss>>account>>ip>>adord>>frd;
    account=account.substr(8);
    ip=ip.substr(3);
    frd=frd.substr(7);
    std::cout<<account<<" "<<ip<<" "<<frd<<" "<<adord<<std::endl;
    if(U_NeoDB::set_ip(account, ip)==-1)
        return -1;
    if(adord=="add")
    {
        if(U_NeoDB::add_friends(account, frd)==-1)
            return -2;
    }
    else if(adord=="delete")
    {
        if(U_NeoDB::delete_friends(account, frd)==-1)
            return -3;
    }
    return 1;
}

int Update::upd_fl(const char * msg)
{
    std::istringstream iss(msg);
    string account, ip, adord, frd, location;
    iss>>account>>ip>>adord>>frd;
    account=account.substr(8);
    ip=ip.substr(3);
    frd=frd.substr(7);
    if(get_ip_location(ip, location)!=1)
        location="unknown";
    if(U_NeoDB::set_location(account, location)==-1)
        return -1;
    if(adord=="add")
    {
        if(U_NeoDB::add_friends(account, frd)==-1)
            return -2;
    }
    else if(adord=="delete")
    {
        if(U_NeoDB::delete_friends(account, frd)==-1)
            return -3;
    }
    return 1;
}

int Update::upd_all(const char *msg)
{
    std::istringstream iss(msg);
    string account, ip, adord, frd, location;
    iss>>account>>ip>>adord>>frd;
    account=account.substr(8);
    ip=ip.substr(3);
    frd=frd.substr(7);
    if(get_ip_location(ip, location)!=1)
        location="unknown";
    if(U_NeoDB::set_ip(account, ip)==-1)
        return -1;
    if(U_NeoDB::set_location(account, location)==-1)
        return -2;
    if(adord=="add")
    {
        if(U_NeoDB::add_friends(account, frd)==-1)
            return -3;
    }
    else if(adord=="delete")
    {
        if(U_NeoDB::delete_friends(account, frd)==-1)
            return -6;
    }
    return 1;
}

int Update::upd_info(const char * msg, string &fip)
{
    string account(msg);
    account=account.substr(8);
    if((fip=U_NeoDB::get_all_fip(account))=="err")
        return -1;
    return 1;
}
/*
 * keep_alive function is used for update information after login
 */
int Action::keep_alive(const char * msg, unsigned char flag, unsigned char reserved, string & rip)
{
    int ret=0;
    switch(flag&L_MASK)
    {
        case UPD_IP :
            if(Update::upd_ip(msg)==-1)
                ret=-1;//update ip error
            break;
        case UPD_LOC :
            if(Update::upd_loc(msg)==-1)
                ret=-2;//update location error
            break;
        case UPD_FRD :
            if((ret=Update::upd_frd(msg))==-1)
                ret=-3;//add friend error
            else if(ret==-2)
                ret=-4;//delete friend error
            else
                ret=0;
            break;
        case UPD_INFO :
            if(Update::upd_info(msg, rip)==-1)
                ret=-5;//request friends ip error
            break;
        case UPD_IP|UPD_LOC :
            if((ret=Update::upd_il(msg))==-1)
                ret=-6;//update ip error;
            else if(ret==-2)
                ret=-7; //update ip OK, update location error;
            else
                ret =0;
            break;
        case UPD_IP|UPD_FRD :
            if((ret=Update::upd_if(msg))==-1)
                ret=-8; //set ip error;
            else if(ret==-2)
                ret=-9; //set ip ok, add friends error;
            else if(ret==-3)
                ret=-10; //set ip ok, delete friends error;
            else
                ret=0;
            break;
        case UPD_FRD|UPD_LOC :
            if((ret=Update::upd_fl(msg))==-1)
                ret=-11;//set location error;
            else if(ret==-2)
                ret=-12;//set location OK, add friends error;
            else if(ret==-3)
                ret=-13;//set location OK, delete friends error;
            else
                ret=0;
            break;
        case UPD_IP|UPD_LOC|UPD_FRD :
            if((ret=Update::upd_all(msg))==-1)
                ret=-14;//set ip error;
            else if(ret==-2)
                ret=-15;//set ip OK, set location error;
            else if(ret==-3)
                ret=-16;//set ip, location OK, add friends error;
            else if (ret==-6)
                ret=-17;//set ip, location ok, delete friends error;
            break;
        default:
            ret=-256;
            break;
    }
    return ret;
}

int proc_msg(const char * msg, string & param, int soc)
{
    struct rp2p *rpp=(struct rp2p *)msg;
    int ret=0;
    Sock sock(soc);
    switch(rpp->confld&H_MASK)
    {
        case LOG_IN :
            if((ret=Action::login(msg+sizeof(struct rp2p), param))==-1)
                ret=-1; //-1 stand for query pwd error for login
            else if(ret==-2)
                ret=-2; //-2 stand for neodb login error
            else if(ret==-3)
                ret=-3; //-3 stand for set client error
            else if(ret==-5)
                ret=-5; //-4 stand for set ip error;
            else if(ret==-6)
                ret=-6; //-6 stand for set location error;
            else if(ret==-7)
                ret=-7; //-7 stand for get all friend ip error;
            else
            {
                ret=0;
                sock.send_msg("Login OK");
            }
            if(ret!=0)
                sock.send_msg("error");
            break;
        case SIGN_ON :
            ret=Action::sign_on(msg+sizeof(struct rp2p));
            if(ret==1)
                sock.send_msg("Sign on OK");
            if(ret==-1)
                sock.send_msg("account already exist");
            ret+=-7;
            break;
        case LOG_OUT :
            ret=Action::log_out(msg+sizeof(struct rp2p));
            ret+=-13;
            break;
        case LOGGED :
            ret=Action::keep_alive(msg+sizeof(struct rp2p), rpp->confld&L_MASK, rpp->reserv, param);
            if(param.size()>6)
                sock.send_msg(param);
            ret+=-25;
            break;
        default:
            ret=-256;
            break;
    }
    return ret;
}
