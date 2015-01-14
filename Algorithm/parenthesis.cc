#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

void func()
{
    ifstream ifs("input");
    if(!ifs.is_open())
    {
        exit(0);
    }
    ofstream ofs("output");
    if(!ofs.is_open())
    {
        exit(0);
    }
    int num_t;
    ifs>>num_t;
    int index=1;
    int B, L, N;
    ofs<<setprecision(6);
    ofs<<setiosflags(ios::fixed);
    while(ifs>>B)
    {
        ifs>>L>>N;
        vector<int> sumvec;
        sumvec.push_back(1);
        for(int i=2; i<=L; i++)
        {
            int lsu=(i*(i+1))/2;
            sumvec.push_back(lsu);
        }
        long double tot_v=B*750.0;
        for(int i=0; i<L-1; i++)
        {
            tot_v=tot_v-(sumvec[i]*250.0);
        }
        tot_v/=sumvec[L-1];
        if(tot_v>250.0)
            tot_v=N*250.0;
        if(tot_v<=10e-6)
            tot_v=0.0;
        ofs<<"Case #"<<index<<": "<<tot_v<<endl;
        index++;
    }
    ifs.close();
    ofs.close();
}

int main()
{
    func();
    return 0;
}