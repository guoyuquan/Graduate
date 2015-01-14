#include <string>

static std::string serv_ip;
static std::string log_acc;

class Conn
{
public:
    static int sign_on(const std::string &, const std::string &);
    static int login(const std::string &, const std::string &);
    static int log_out(const std::string &);
    static int update_ip(const std::string &);
    static int request_fip(const std::string &, std::string &);
    static int adfrd(const std::string &, const std::string &, int);
};