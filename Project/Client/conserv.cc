#include "conserv.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

struct rp2p{
    unsigned char confld;
    unsigned char reserv;
    short seq;
    short ack;
    short cksum;
};

class Sock
{
public:
    Sock();
    int send_msg(const std::string & msg);
    int recv_msg(std::string & msg);
    ~Sock();
private:
    int sock;
    int valid;
};

Sock::Sock()
{
    sock=socket(AF_INET, SOCK_STREAM, 0);
    if(sock==-1)
    {
        valid=-1;
        return;
    }
    std::cout<<sock<<std::endl;
    valid=1;
    sockaddr_in sa;
    sa.sin_family=AF_INET;
    sa.sin_port=htons(6868);
    sa.sin_addr.s_addr=inet_addr("127.0.0.1");//(serv_ip.c_str());
    if(connect(sock, (sockaddr*)&sa, sizeof(sa))==-1)
    {
        valid=2;
        std::cout<<strerror(errno)<<std::endl;
        return;
    }
    valid=0;
}

Sock::~Sock()
{
    if(sock>=0)
        close(sock);
}

int Sock::send_msg(const std::string & msg)
{
    if(valid!=0)
        return -256;
    int ret;
    ret=send(sock, msg.c_str(), msg.size(), 0);
    return ret;
}

int Sock::recv_msg(std::string &msg)
{
    timeval tv;
    tv.tv_sec=2;
    tv.tv_usec=0;
    if(setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(timeval))!=0)
        return -3;
    char rcv_buf[1500];
    memset(rcv_buf, 0, 1500);
    int ret=recv(sock, rcv_buf, 1500, 0);
    if(ret!=-1)
        msg=std::string(rcv_buf+sizeof(rp2p));
    return ret;
}


/*
 **************************
 confld|reserv|sequence_num
 **************************
 acknowledge  |checksum
 **************************
 */
#define LOG_IN   0x80  //when this bit is set, it's login action
#define SIGN_ON  0x40  //when this bit is set, it's register action
#define LOG_OUT  0x20  //when this bit is set, it's log out action
#define LOGGED   0x10  //when this bit is set, the user has complete login action
/*
 * following four all need the logged flag is set, Otherwise, error occur
 */
#define UPD_IP   0x08  //this bit set for users update it's IP
#define UPD_LOC  0x04  //this bit set for users to update its location
#define UPD_FRD  0x02  //this bit set for users to update friendship
#define UPD_INFO 0x01  //this bit set for request update peer's IP

#define H_MASK   0xf0
#define L_MASK   0x0f

int Conn::sign_on(const std::string & account, const std::string & pwd)
{
    struct rp2p rpp;
    rpp.confld=SIGN_ON;
    rpp.reserv=~0;
    rpp.seq=~0;
    rpp.ack=~0;
    rpp.cksum=~0;
    char buf[1500];
    memset(buf, 0, 1500);
    memcpy(buf, (void *)&rpp, sizeof(rpp));
    system("ifconfig en0 inet >> data/ip");
    std::ifstream ifs("data/ip");
    if(!ifs.is_open())
    {
        std::cerr<<">error to sign on, please try again!"<<std::endl;
        return 0;
    }
    std::string ip;
    getline(ifs, ip);
    getline(ifs, ip);
    ifs.close();
    std::istringstream iss(ip);
    iss>>ip>>ip;
    //std::cout<<ip<<std::endl;
    std::string msg="account:"+account+" password:"+pwd+" ip:"+ip;
    memcpy(buf+sizeof(rp2p), msg.c_str(), msg.size());
    //std::cout<<msg<<std::endl;
    /*
     * here need send message to server and receive message from server to judge 
     * whether login action has succeed.
     */
    Sock sock;
    if(sock.send_msg(buf)==-256)
    {
        std::cerr<<">error: connect to server"<<std::endl;
        return 1;
    }
    std::string rcv_str;
    int rcv_cnt=0;
    while(sock.recv_msg(rcv_str)==-1)
    {
        if(rcv_cnt==2)
        {
            std::cerr<<">network unavailable."<<std::endl;
            return -1;
        }
        sock.send_msg(buf);
        rcv_cnt++;
    }
    std::cout<<">"<<rcv_str<<std::endl;
    if(rcv_str=="Sign on OK")
        return 0;
    return 1;
}

int Conn::login(const std::string & account, const std::string & pwd)
{
    struct rp2p rpp;
    rpp.confld=LOG_IN;
    rpp.reserv=~0;
    rpp.seq=~0;
    rpp.ack=~0;
    rpp.cksum=~0;
    char buf[1500];
    memset(buf, 0, 1500);
    memcpy(buf, (void *)&rpp, sizeof(rp2p));
    system("ifconfig en0 inet >> data/ip");
    std::ifstream ifs("data/ip");
    if(!ifs.is_open())
    {
        std::cerr<<">error to login, please try again!"<<std::endl;
        return 0;
    }
    std::string ip;
    getline(ifs, ip);
    getline(ifs, ip);
    ifs.close();
    std::istringstream iss(ip);
    iss>>ip>>ip;
    std::string msg="account:"+account+" password:"+pwd+" client:IOS"+" ip:"+ip;
    //std::cout<<msg<<std::endl;
    memcpy(buf+sizeof(rp2p), msg.c_str(), msg.size());
    /*
     * send message to server
     */
    std::cout<<buf+sizeof(rp2p)<<std::endl;
    Sock sock;
    if(sock.send_msg(buf)==-256)
    {
        std::cerr<<">error: connect to server"<<std::endl;
        return 1;
    }
    std::string rcv_str;
    int rcv_cnt=0;
    while(sock.recv_msg(rcv_str)==-1)
    {
        if(rcv_cnt==3)
        {
            std::cerr<<">network unavailable."<<std::endl;
            return -1;
        }
        sock.send_msg(buf);
        rcv_cnt++;
    }
    std::cout<<">"<<rcv_str<<std::endl;
    if(rcv_str=="Login OK")
        return 0;
    return 1;
}

int Conn::log_out(const std::string &account)
{
    struct rp2p rpp;
    rpp.confld=LOG_OUT;
    rpp.reserv=~0;
    rpp.seq=~0;
    rpp.ack=~0;
    rpp.cksum=~0;
    char buf[1500];
    memset(buf, 0, 1500);
    memcpy(buf, (void *)&rpp, sizeof(rp2p));
    std::string msg="account:"+account;
    memcpy(buf+sizeof(rp2p),msg.c_str(), msg.size());
    /*
     * send message to server
     */
    Sock sock;
    if(sock.send_msg(buf)==-256)
    {
        std::cerr<<">error: connect to server"<<std::endl;
        return 1;
    }
    std::string rcv_str;
    int rcv_cnt=0;
    while(sock.recv_msg(rcv_str)==-1)
    {
        if(rcv_cnt==2)
        {
            std::cerr<<">network unavailable."<<std::endl;
            return -1;
        }
        sock.send_msg(buf);
        rcv_cnt++;
    }
    std::cout<<">"<<rcv_str<<std::endl;
    return 1;
}

int Conn::update_ip(const std::string & account)
{
    struct rp2p rpp;
    rpp.confld=LOGGED|UPD_IP|UPD_LOC;
    rpp.reserv=~0;
    rpp.seq=~0;
    rpp.ack=~0;
    rpp.cksum=~0;
    char buf[1500];
    memset(buf, 0, 1500);
    memcpy(buf, (void *)&rpp, sizeof(rp2p));
    system("ifconfig en0 inet >> data/ip");
    std::ifstream ifs("data/ip");
    if(!ifs.is_open())
    {
        //std::cerr<<"error to s, please try again!"<<std::endl;
        return 0;
    }
    std::string ip;
    getline(ifs, ip);
    getline(ifs, ip);
    ifs.close();
    std::istringstream iss(ip);
    iss>>ip>>ip;
    std::string msg="account:"+account+" ip:"+ip;
    memcpy(buf+sizeof(rp2p), msg.c_str(), msg.size());
    /*
     * send to server
     */
    Sock sock;
    if(sock.send_msg(buf)==-256)
    {
        //std::cerr<<"error: connect to server"<<std::endl;
        return 1;
    }
    std::string rcv_str;
    int rcv_cnt=0;
    while(sock.recv_msg(rcv_str)==-1)
    {
        if(rcv_cnt==2)
        {
            std::cerr<<">network unavailable."<<std::endl;
            return -1;
        }
        sock.send_msg(buf);
        rcv_cnt++;
    }
    //std::cout<<rcv_str<<std::endl;
    return 1;
}

int Conn::request_fip(const std::string & account, std::string & rcv_str)
{
    struct rp2p rpp;
    rpp.confld=LOGGED|UPD_INFO;
    rpp.reserv=~0;
    rpp.seq=~0;
    rpp.ack=~0;
    rpp.cksum=~0;
    char buf[1500];
    memset(buf, 0, 1500);
    memcpy(buf, (void *)&rpp, sizeof(rp2p));
    std::string msg="account:"+account;
    memcpy(buf+sizeof(rp2p), msg.c_str(), msg.size());
    /*
     * send to server
     */
    Sock sock;
    if(sock.send_msg(buf)==-256)
    {
        //std::cerr<<"error: connect to server"<<std::endl;
        return 1;
    }
    //std::string rcv_str;
    int rcv_cnt=0;
    while(sock.recv_msg(rcv_str)==-1)
    {
        if(rcv_cnt==2)
        {
            std::cerr<<">network unavailable."<<std::endl;
            return -1;
        }
        sock.send_msg(buf);
        rcv_cnt++;
    }
    //std::cout<<rcv_str<<std::endl;
    return 1;
}

int Conn::adfrd(const std::string & account, const std::string & frd, int flag)
{
    struct rp2p rpp;
    rpp.confld=LOGGED|UPD_FRD;
    rpp.reserv=~0;
    rpp.seq=~0;
    rpp.ack=~0;
    rpp.cksum=~0;
    char buf[1500];
    memset(buf, 0, 1500);
    memcpy(buf, (void *)&rpp, sizeof(rp2p));
    std::string msg;
    if(flag==1)
    {
        msg="account:"+account+" add"+" friend:"+frd;
    }
    else
        msg="account:"+account+" delete"+" friend:"+frd;
    memcpy(buf+sizeof(rp2p), msg.c_str(), msg.size());
    /*
     * send to server
     */
    Sock sock;
    if(sock.send_msg(buf)==-256)
    {
        std::cerr<<">error: connect to server"<<std::endl;
        return 1;
    }
    std::string rcv_str;
    int rcv_cnt=0;
    while(sock.recv_msg(rcv_str)==-1)
    {
        if(rcv_cnt==2)
        {
            std::cerr<<">network unavailable."<<std::endl;
            return -1;
        }
        sock.send_msg(buf);
        rcv_cnt++;
    }
    std::cout<<">"<<rcv_str<<std::endl;
    return 1;
}
