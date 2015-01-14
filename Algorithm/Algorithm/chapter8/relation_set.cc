#include<iostream>

class Disj_Set{
public:
    Disj_Set(int n):sz(n), dis(new int[n]){}
    void set_union(int root1, int root2);
    int find(int x);
    void print();
    ~Disj_Set();
private:
    int sz;
    int * dis;
};

void Disj_Set::set_union(int root1, int root2)
{
    if(root1>sz||root2>sz)
    {
        std::cout<<"out of range"<<std::endl;
        return;
    }
    dis[root2-1]=root1;
}

int Disj_Set::find(int x)
{
    if(x>sz)
    {
        std::cout<<"out of range"<<std::endl;
        return -1;
    }
    if(dis[x-1]<=0)
        return x;
    else
        return (find(dis[x-1]));
}

void Disj_Set::print()
{
    for(int i=0; i<sz;i++)
        std::cout<<dis[i]<<" ";
    std::cout<<std::endl;
}

Disj_Set::~Disj_Set()
{
    delete[]dis;
}

int main()
{
    Disj_Set dis(10);
    dis.print();
    dis.set_union(1, 5);
    std::cout<<dis.find(5)<<std::endl;
    dis.print();
    return 0;
}