#include "rp2p.h"
#include <iostream>

int main()
{
    std::string s;
    //std::cout<<Action::login("account:JERRY password:jerry client:WP ip:54.86.202.236", s)<<std::endl;
    //std::cout<<Action::log_out("account:JERRY")<<std::endl;
    //std::cout<<Action::keep_alive("account:JERRY ip:54.86.202.236", UPD_LOC, 0, s)<<std::endl;
    std::cout<<Action::keep_alive("account:123456", UPD_INFO, 0, s)<<std::endl;
    std::cout<<s<<std::endl;
    const std::string &str=s;
    return 0;
}