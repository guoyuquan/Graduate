#include <iostream>
#include <fstream>
using namespace std;

void func()
{
    ifstream ifs("input");
    int num_t;
    ofstream ofs("output");
    ifs>>num_t;
    int M, N, ret=1, index=1;
    while(ifs>>M)
    {
        ifs>>N;
        ret=1;
        cout<<M<<" "<<N<<endl;
        if(M==N)
        {
            for(int i=1; i<=M; i++)
            {
                ret*=i;
            }
            ofs<<"Case #"<<index<<": "<<ret<<endl;
        }
        else
        {
            int sub=N-M+1;
            for(int i=1; i<=N; i++)
            {
                if(i<=sub)
                    continue;
                ret*=i;
            }
            ret*=M;
            ofs<<"Case #"<<index<<": "<<ret%10e9+7<<endl;
        }
        index++;
        
    }
    ofs.close();
    ifs.close();
}

int main()
{
    func();
    return 0;
}
