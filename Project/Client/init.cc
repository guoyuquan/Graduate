#include "init.h"
#include "conserv.h"
#include <iostream>

void init()
{
    std::cout<<">Press Y to sign on, or enter account"<<std::endl;
    std::cout<<">account:";
    std::cin>>log_acc;
    std::string pwd;
    if(log_acc=="Y"||log_acc=="y")
    {
        do
        {
            std::cout<<">account:";
            std::cin>>log_acc;
            std::cout<<">password:";
            std::cin>>pwd;
        }while(Conn::sign_on(log_acc, pwd)!=0);
        std::cout<<">account:";
        std::cin>>log_acc;
    }
    std::cout<<">password:";
    std::cin>>pwd;
    while(Conn::login(log_acc, pwd)!=0)
    {
        std::cout<<">account:";
        std::cin>>log_acc;
        std::cout<<">password:";
        std::cin>>pwd;
    }
}