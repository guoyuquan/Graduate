#include<map>
#include<iostream>

int main()
{
    std::map<int, int> imap;
    std::cout<<imap.size()<<std::endl;
    imap[10]++;
    std::cout<<imap.size()<<std::endl;
    std::cout<<imap[0]<<std::endl;
    std::cout<<(--imap.end())->first<<std::endl;
    std::cout<<imap.size()<<std::endl;
    const const int i=0;
    return 0;
}