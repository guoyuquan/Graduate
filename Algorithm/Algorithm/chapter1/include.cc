#include<iostream>
#include<fstream>

void read_file(const std::string &s)
{
    std::ifstream ifs(s);
    if(!ifs.is_open())
    {
        std::cout<<"error: open file"<<std::endl;
        return;
    }
    std::string line;
    while (getline(ifs, line))
    {
        if(line.substr(0,8)=="#include")
        {
            line=line.substr(8);
            read_file(line);
            continue;
        }
        std::cout<<line<<std::endl;
    }
}

int main()
{
    read_file("include.cc");
    return 0;
}