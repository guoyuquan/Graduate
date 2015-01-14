#include <iostream>
#include "userdb.h"

#define server      "localhost"
#define user        "root"
#define password    "guoyuquan"
#define database    "Users"

/*
 *Users DB, users table, column account(primary key), pwd
 */

DBConn::DBConn()
{
    conn = mysql_init(NULL);
    mysql_real_connect(conn, server, user, password, database, 0, NULL, 0);
}
/*when the query is finished, close connection, forbid resource leak*/
DBConn::~DBConn()
{
    mysql_close(conn);
}

string DBConn::query_pwd(const string & account)
{
    if(mysql_query(conn, string("select pwd from Users.users where users.account='"+account+"'").c_str()))
    {
        std::cerr<<"error: query pwd for "<<account<<std::endl;
        return "";
    }
    MYSQL_RES *res=mysql_use_result(conn);
    if(res==NULL)
        return "";
    MYSQL_ROW row=mysql_fetch_row(res);
    if(row==NULL)
        return "";
    string ret(row[0]);
    mysql_free_result(res);
    return ret;
}

int DBConn::insert(const string & account, const string & pwd)
{
    if(mysql_query(conn, string("INSERT INTO users (account, pwd) VALUES ('"+account+"', '"+pwd+"')").c_str()))
    {
        std::cerr<<"error: insert"<<std::endl;
        return -1;
    }
    return 0;
}


int DBConn::update(const string &account, const string & pwd)
{
    if(mysql_query(conn, string("update users set pwd='"+pwd+"' where account='"+account+"'").c_str()))
    {
        std::cerr<<"error: update"<<std::endl;
        return -1;
    }
    return 0;
}

