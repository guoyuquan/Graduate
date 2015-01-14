#include <mysql.h>
#include <string>
using std::string;

class DBConn{
public:
    DBConn();
    string query_pwd(const string &);   //used for check password
    int insert(const string &, const string &); //for new user
    int update(const string &, const string &); //change passwd
    ~DBConn();
private:
    MYSQL *conn;
    DBConn(DBConn &);
    DBConn operator=(DBConn);
};