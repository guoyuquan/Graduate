#include "command.h"
#include "conserv.h"
#include "init.h"
#include <iostream>

int main(int argc, char * argv[])
{
    if(argc<2)
    {
        std::cout<<">please provide server ip"<<std::endl;
        return 0;
    }
    serv_ip=std::string(argv[1]);
    //std::cout<<serv_ip<<std::endl;
    init();
    std::cout<<">";
    std::string temp;
    while(getline(std::cin, temp))
    {
        proc_comm(temp);
        std::cout<<">";
    }
    return 0;
}