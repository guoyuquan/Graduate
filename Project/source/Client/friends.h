#include <vector>
#include <string>

struct f_info
{
    f_info():flag(0){};
    std::string account;
    std::string ip;
    int flag;
};

class Friends
{
public:
    Friends():ava(0){}
    void update_vec(std::vector<f_info>);
    int search_vec(const std::string &, f_info *);
    void list_all();
    std::vector<f_info> retvec(){return fvec;}
private:
    std::vector<f_info> fvec;
    int ava;
};

static Friends friends;