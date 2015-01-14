#include <iostream>
#include <fstream>
#include <string>

int
main()
{
    std::ofstream ifs("a.out");
    if(!ifs.is_open())
    {
        std::cerr<<"error: open file"<<std::endl;
        return 0;
    }
    std::string str;
    ifs<<"what"<<std::endl;
    return 0;
}