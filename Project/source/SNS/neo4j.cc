#include "neo4j.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#define BUFFSIZE 100000

int get_ip_location(const string & ipstr, string & xml)
{
    int sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock==-1)
    {
        //cout<<"ERROR: open socket."<<endl;
        return -1;
    }
    //cout<<"start"<<endl;
    sockaddr_in sa;
    sa.sin_family=AF_INET;
    sa.sin_port=htons(80);
    sa.sin_addr.s_addr=inet_addr("54.86.202.236");
    bool flag=false;
    int error=-1, len;
    unsigned long one=1;
    //ioctl(sock, FIONBIO, &one);
    int se;
    //cout<<"here"<<endl;
    if(connect(sock,(sockaddr *)&sa, sizeof(sa))==-1)
    {
        //cout<<"connect error"<<endl;
        close(sock);
        return -1;
    }
    string request="GET /iplocation/v1.7/locateip?key=SAK2VL7X5U4D3554K36Z&ip="+ipstr+"&format=XML HTTP/1.1\r\nHost:api.ipaddresslabs.com\r\nAccept:text/html\r\nConnection:keep-alive\r\nUser-Agent:Mozilla/5.0(Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/527.74.9 (KHTML, like Gecko) Version/7.0.2 Safari/537.74.9\r\n\r\n";
    if(send(sock,request.c_str(),request.size(),0)==-1)
    {
        //cout<<"faile to send."<<endl;
        close(sock);
        return -1;
    }
    timeval tv;
    tv.tv_sec=3;
    tv.tv_usec=0;
    if(setsockopt(sock,SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(timeval))!=0)
    {
        //cout<<"ERROR: set receive timer."<<endl;
        close(sock);
        return -1;
    }
    char *xmlbuf;
    xmlbuf=new char[15000];
    memset(xmlbuf,0,15000);
    int bytesRead=0;
    int ret=1;
    while(ret>0)
    {
        ret=recv(sock,xmlbuf+bytesRead,15000-bytesRead,0);
        if(ret>0)
        {
            bytesRead+=ret;
            tv.tv_sec=3;
            setsockopt(sock,SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(timeval));
        }
        //cout<<ret<<" ";
    }
    //cout<<endl;
    xmlbuf[bytesRead]='\0';
    //cout<<xmlbuf<<endl;
    xml=string(xmlbuf);
    delete []xmlbuf;
    /*this part need further consideration*/
    std::istringstream iss(xml);
    string str;
    while(iss>>str)
    {
        //std::cout<<str<<std::endl;
        if((str.size()>13)&&(str.substr(0,6)=="<city>"))
        {
            //cout<<"bingo"<<endl;
            xml=str.substr(6, str.size()-13);
            close(sock);
            return 1;
        }
    }
    
    close(sock);
    return 0;
}

NeoDB::NeoDB()
{
    if((sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==-1)
        state=false;
    /*state to indicate the validation of socket*/
    else
        state=true;
    if(!state)
        return;
    sockaddr_in sa;
    sa.sin_family=AF_INET;
    sa.sin_port=htons(7474);
    sa.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(connect(sock, (sockaddr *)&sa, sizeof(sa))==-1)
        state=false;
    else
        state=true;
}

NeoDB::~NeoDB()
{
    if(state)
        close(sock);
}
/*
 *unified interface to access the neo4j database, -1 for error, others for OK
 */
int NeoDB::neo_query(const string & query, string & result)
{
    std::ostringstream oss;
    oss<<query.size();
    string len=oss.str();
    string request="POST http://localhost:7474/db/data/cypher HTTP/1.1\r\nHost: localhost:7474\r\nAccept: application/json; charset=UTF-8\r\nContent-Type: application/json\r\nContent-Length: "+len+"\r\n\r\n"+query;//need check whether the get method can do the trick
    send(sock, request.c_str(), request.size(), 0);
    char * buff=new char [BUFFSIZE];
    if(buff==NULL)
        return -1;
    memset(buff, 0, BUFFSIZE);
    recv(sock, buff, BUFFSIZE, 0);
    result=string(buff);
    delete [] buff;
    return 1;
}

int U_NeoDB::create_account(const string & account)
{
    string request = "{ \"query\" : \"CREATE (n:User {account : {acc} }) return n \", \"params\" : {\"acc\" : \""+account+"\" } }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return -1;
    return 1;
}

string U_NeoDB::get_client(const string & account)
{
    /*request is a string for the neo4j cypher, need encode account in it*/
    string request="{ \"query\" : \"MATCH (a:User), (a)-[r:platform]->(b) WHERE a.account = {acc} return b \", \"params\" : {\"acc\" : \"" + account + "\"}}";
    string result; //result is a parameter to the NeoDB::neo_query function, and filled by the neo_query function and return by this function
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return "err";
    string temp="client";
    int index=0;
    for(index=0; index<result.size(); index++)
    {
        int j=0;
        if(result[index]==temp[0])
            for(j=0; j<6&&result[index++]==temp[j++]; )
                ;
        if(j==6)
            break;
    }
    /* here need to find the client type */
    if(index<result.size())
    {
        index+=5;
        int end=index;
        for(; end<result.size()&&result[end]!='\"'; end++)
            ;
        result=result.substr(index, end-index);
    }
    else
    {
        return "err";
    }
    return result;
}

int U_NeoDB::set_client(const string &account, const string & client)
{
    /* first need to delete the existed platform relationship */
    string request = "{ \"query\" : \"MATCH (a:User), (b:C_Type), (a)-[r:platform]->(b) WHERE a.account = {acc} DELETE r\", \"params\" : {\"acc\" : \""+account+"\"} }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return -1;
    request = "{ \"query\" : \"MATCH (a:User), (b:C_Type) WHERE a.account = {acc} AND b.client = {cli} CREATE (a)-[r:platform]->(b) RETURN r\", \"params\" : {\"acc\" : \""+account+"\", \"cli\" : \""+client+"\"} }";
    if(neo.neo_query(request, result)==-1)
        return -1;
    return 1;
}

int U_NeoDB::add_friends(const string & account, const string & add_acc)
{
    string request = "{ \"query\" : \"MATCH (a:User), (b:User) WHERE a.account = {acc1} AND b.account = {acc2} CREATE (a)-[r:friend]->(b) RETURN r\", \"params\" : {\"acc1\" : \"" +account+"\", \"acc2\" :\""+add_acc+"\"} }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return -1;
    return 1;
}

int U_NeoDB::delete_friends(const string & account, const string & d_acc)
{
    string request = "{ \"query\" : \"MATCH (a:User), (b:User), (a)-[r]->(b) WHERE a.account = {acc1} AND b.account = {acc2} DELETE r\", \"params\" : {\"acc1\" : \"" +account+"\", \"acc2\" : \""+d_acc+"\"} }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return -1;
    return 1;
}

string U_NeoDB::get_ip(const string &account)
{
    string request = "{ \"query\" : \"MATCH (a:User), (a)-[r:login_on]->(b) WHERE a.account={acc} RETURN b\", \"params\" : {\"acc\" : \""+account+"\"} }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return "err";
    string temp="ip\" :";
    /*
     *following part parse the data returned by the database
     */
    int index=0;
    for(index=0; index<result.size(); index++)
    {
        int j=0;
        if(result[index]==temp[0])
            for(j=0; j<4&&result[index++]==temp[j++]; )
                ;
        if(j==4)
            break;
    }
    if(index<result.size())
    {
        index+=3;
        int end=index;
        for(; end<result.size()&&result[end]!='\"'; end++)
            ;
        result=result.substr(index, end-index);
    }
    else
    {
        return "err";
    }
    return result;
}

int U_NeoDB::set_ip(const string & account, const string & ip)
{
    /*
     *first delete existed relationship and ip node, and create new node, and then
     *add relationship
     */
    string request = "{ \"query\" : \"MATCH (n:User), (n)-[r:login_on]->(m) WHERE n.account={acc} DELETE r, m\", \"params\" : { \"acc\" : \""+account+"\"} }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return -1;
    request = "{ \"query\" : \"CREATE (n:IP {ip : {ip1} }) RETURN n\", \"params\" : { \"ip1\" : \""+ip+"\"} }";
    if(neo.neo_query(request, result)==-1)
        return -1;
    request = "{ \"query\" : \"MATCH (a:User), (b:IP) WHERE a.account = {acc1} AND b.ip = {acc2} CREATE (a)-[r:login_on]->(b) RETURN r\", \"params\" : {\"acc1\" : \"" +account+"\", \"acc2\" :\""+ip+"\"} }";
    if(neo.neo_query(request, result)==-1)
        return -1;
    return 1;
}

string U_NeoDB::get_all_fip(const string & account)
{
    string request = "{ \"query\" : \"MATCH (a:User), (b:User), (a)-[:friend]->(b), (b)-[:login_on]->(c), (b)-[:login_status]->(d) WHERE a.account = {acc1} AND d.status='online' RETURN b, c\", \"params\" : {\"acc1\" : \"" +account+"\" } }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return "err";
    return result;
}

int U_NeoDB::set_last_login(const string & account, const string & llogin)
{
    /*
     *time format hh:mm:ss,dd/mm/yyyy
     */
    string request = "{ \"query\" : \"CREATE (n:Time {time : {tm} }) RETURN n\", \"params\" : {\"tm\" : \""+llogin+"\"} }";
    //std::cout<<request<<std::endl;
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return -1;
    //std::cout<<result<<std::endl;
    request = "{ \"query\" : \"MATCH (n:User), (n)-[r:login_time]->(m) WHERE n.account={acc} DELETE r,m\", \"params\" : {\"acc\" : \""+account+"\"} }";
    //std::cout<<result<<std::endl;
    if(neo.neo_query(request, result)==-1)
        return -1;
    request = "{ \"query\" : \"MATCH (n:User), (m:Time) WHERE n.account={acc} AND m.time={tm} CREATE (n)-[r:login_time]->(m) RETURN r\", \"params\" : { \"acc\" : \""+account+"\",\"tm\" : \""+llogin+"\"} }";
    if(neo.neo_query(request, result)==-1)
        return -1;
    //std::cout<<result<<std::endl;
    return 1;
}

string U_NeoDB::get_last_login(const string &account)
{
    string request = "{ \"query\" : \"MATCH (n:User), (m:Time), (n)-[r:login_time]->(m) WHERE n.account={acc} RETURN m\", \"params\" : { \"acc\" : \""+account+"\" } }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return "err";
    string temp="time\" :";
    /*
     *following part parse the data returned by the database
     */
    int index=0;
    for(index=0; index<result.size(); index++)
    {
        int j=0;
        if(result[index]==temp[0])
            for(j=0; j<6&&result[index++]==temp[j++]; )
                ;
        if(j==6)
            break;
    }
    if(index<result.size())
    {
        index+=3;
        int end=index;
        for(; end<result.size()&&result[end]!='\"'; end++)
            ;
        result=result.substr(index, end-index);
    }
    else
    {
        return "err";
    }
    return result;
}

int U_NeoDB::is_login(const string &account)
{
    string request = "{ \"query\" : \"MATCH (n:User), (m:Login), (n)-[r:login_status]->(m) WHERE n.account={acc} RETURN m, r\", \"params\" : { \"acc\" : \""+account+"\" } }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return -1;
    std::cout<<result<<std::endl;
    string temp="status\" :";
    /*
     *following part parse the data returned by the database
     */
    int index=0;
    for(index=0; index<result.size(); index++)
    {
        int j=0;
        if(result[index]==temp[0])
            for(j=0; j<8&&result[index++]==temp[j++]; )
                ;
        if(j==8)
            break;
    }
    if(index<result.size())
    {
        index+=3;
        int end=index;
        for(; end<result.size()&&result[end]!='\"'; end++)
            ;
        result=result.substr(index, end-index);
    }
    else
    {
        return -1;
    }
    if(result=="online")
        return 1;
    return 0;
}

int U_NeoDB::login(const string & account, int status)
{
    /*
     *status 1 stand for login, other status stand for offline
     */
    string request="{ \"query\" : \"MATCH (n:User), (m:Login),(n)-[r:login_status]->(m) WHERE n.account={acc} DELETE r\", \"params\" : { \"acc\" : \""+account+"\" } }";
    NeoDB neo;
    string result;
    if(neo.neo_query(request, result)==-1)
        return -1;
    if(status==1)
        request="{ \"query\" : \"MATCH (n:User), (m:Login) WHERE n.account={acc} AND m.status='online' CREATE  (n)-[r:login_status]->(m) RETURN m, r\", \"params\" : { \"acc\" : \""+account+"\" } }";
    else
        request="{ \"query\" : \"MATCH (n:User), (m:Login) WHERE n.account={acc} AND m.status='offline' CREATE  (n)-[r:login_status]->(m) RETURN m, r\", \"params\" : { \"acc\" : \""+account+"\" } }";
    if(neo.neo_query(request, result)==-1)
        return -1;
    return 1;
}

int U_NeoDB::set_preference(const string & account, const string &cgy, const string & subcgy)
{
    /*
     *to easy to access the category and preference level, each user has its own 
     *preference state, and for convienient to access and efficiency to access
     *0 stands for news, 1 stands for games, 2 stands for food, 3 stands for movies
     *4 stands for constellation, 5 stands for video, for the demo, all the sub 
     *category is 0, it means that there no sub category stored in the DB.
     */
/*
 *the format is 1:0:level category, sub category and preference level respectively
 */
    string request, preference;
    string result;
    NeoDB neo;
    if((preference=get_preference(account))=="err")
    {
        request="{ \"query\" : \"CREATE (n:Preference { category : {cgy} }) RETURN n\", \"params\" : {\"cgy\" : \""+cgy+":"+subcgy+":1;1:0:0;2:0:0\"} }";
        if(neo.neo_query(request, result)==-1)
            return -1;
        std::cout<<result<<std::endl;
        request="{ \"query\" : \"MATCH (n:User), (m:Preference) WHERE n.account={acc} AND m.category={cgy} CREATE (n)-[r:prefer]->(m) RETURN r\", \"params\" : { \"acc\" : \""+account+"\", \"cgy\" : \""+cgy+":"+subcgy+":1;1:0:0;2:0:0\"} }";
    }
    else
    {
        request="{ \"query\" : \"MATCH (n:User), (m:Preference), (n)-[r:prefer]->(m) WHERE n.account={acc} DELETE r, m\", \"params\" : { \"acc\" : \""+account+"\"} }";
        if(neo.neo_query(request, result)==-1)
            return -1;
        string temp=cgy+":"+subcgy;
        int i=0;
        for(int i; i<preference.size(); i++)
        {
            int j=0;
            if(preference[i]==temp[0])
                for(j=0; j<temp.size()&&preference[i++]==temp[j++];)
                    ;
            if(j==temp.size())
                break;
        }
        preference[i+1]++;
        request="{ \"query\" : \"CREATE (n:Preference { category : {cgy} }) RETURN n\", \"params\" : {\"cgy\" : \""+preference+"\"} }";
        if(neo.neo_query(request, result)==-1)
            return -1;
        request="{ \"query\" : \"MATCH (n:User), (m:Preference) WHERE n.account={acc} AND m.category={cgy} CREATE (n)-[r:prefer]->(m) RETURN r\", \"params\" : { \"acc\" : \""+account+"\", \"cgy\" : \""+preference+"\"} }";
    }
    if(neo.neo_query(request, result)==-1)
        return -1;
    return 1;
}

string U_NeoDB::get_preference(const string & account)
{
    string request = "{ \"query\" : \"MATCH (n:User), (m:Preference), (n)-[r:prefer]->(m) WHERE n.account={acc} RETURN m\", \"params\" : { \"acc\" : \""+account+"\" } }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return "err";
    //std::cout<<result<<std::endl;
    string temp="category\" : ";
    /*
     *following part parse the data returned by the database
     */
    
    int index=0;
    for(index=0; index<result.size(); index++)
    {
        int j=0;
        if(result[index]==temp[0])
            for(j=0; j<12&&result[index++]==temp[j++]; )
                ;
        if(j==12)
            break;
    }
    if(index<result.size())
    {
        index+=3;
        int end=index;
        for(; end<result.size()&&result[end]!='"'; end++)
            ;
        result=result.substr(index, end-index);
    }
    else
    {
        return "err";
    }
    return result;
}

int U_NeoDB::set_location(const string & account, const string & location)
{
    /*
     *location format is longitude:latitude
     */
    string request = "{ \"query\" : \"CREATE (n:Lg_Location { location : {loc} }) RETURN n\", \"params\" : { \"loc\" : \""+location+"\"} }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return -1;
    request = "{ \"query\" : \"MATCH (n:User), (m:Lg_Location),(n)-[r:login_location]->(m) WHERE n.account={acc} DELETE r, m\", \"params\" : { \"acc\" : \""+account+"\" } }";
    if(neo.neo_query(request, result)==-1)
        return -1;
    request = "{ \"query\" : \"MATCH (n:User), (m:Lg_Location) WHERE n.account={acc} AND m.location={loc} CREATE (n)-[r:login_location]->(m)\", \"params\" : { \"acc\" : \""+account+"\", \"loc\" : \""+location+"\" } }";
    if(neo.neo_query(request, result)==-1)
        return -1;
    return 1;
}

string U_NeoDB::get_freq_location(const string & account)
{
    /*
     *this is used for getting the frequent location, no need to get login location
     *since the login location is already known and used to set, then it can just 
     *compare with the result of this function
     */
    string request="{ \"query\" : \"MATCH (n:User), (m:Freq_Location), (n)-[r:location]->(m) WHERE n.account={acc} RETURN m\", \"params\" : { \"acc\" : \""+account+"\" } }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return "err";
    string temp="location\" :";
    /*
     *following part parse the data returned by the database
     */
    int index=0;
    for(index=0; index<result.size(); index++)
    {
        int j=0;
        if(result[index]==temp[0])
            for(j=0; j<10&&result[index++]==temp[j++]; )
                ;
        if(j==10)
            break;
    }
    if(index<result.size())
    {
        index+=3;
        int end=index;
        for(; end<result.size()&&result[end]!='\"'; end++)
            ;
        result=result.substr(index, end-index);
    }
    else
    {
        return "err";
    }
    return result;
}



int U_NeoDB::set_freq_location(const string & account, const string & location)
{
    /*
     *this function only called when the first time the user register the account
     */
    /*
     *the location format is city, country
     */
    string request="{ \"query\" : \"CREATE (n:Freq_Location { location : {loc} }) RETURN n\", \"params\" : { \"loc\" : \""+location+"\"} }";
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return -1;
    request="{ \"query\" : \"MATCH (n:User), (m:Freq_Location) WHERE n.account={acc} AND m.location={loc} CREATE (n)-[r:location]->(m)\", \"params\" : { \"acc\" : \""+account+"\", \"loc\" : \""+location+"\" } }";
    if(neo.neo_query(request, result)==-1)
        return -1;
    return 1;
}

int L_NeoDB::set_prefer(const string & location, int cgy, int sub_cgy)
{
    string request;
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return -1;
    return 1;
}

string L_NeoDB::get_prefer(const string & location)
{
    string request;
    string result;
    NeoDB neo;
    if(neo.neo_query(request, result)==-1)
        return "err";
    return result;
}