#include <iostream>
#include <string>
#include <vector>

class Records
{
public:
    static void add_rcd(const std::string & account, const std::string & msg);
    static void list(const std::string & account);
};

class Frd_List
{
public:
    static int read(std::vector<std::string> &vec);
    static int fadd(const std::string &);
    static int fdelete(const std::string &);
};