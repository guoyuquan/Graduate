#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;



int func(vector<string> &vec, vector<string> &flag)
{
    for(int i=0; i<vec.size(); i++)
    {
        for(int j=0; j<vec.size(); j++)
        {
            if(vec[i][j]=='*')
            {
                flag[i][j]=-1;
                if(i-1>=0)
                    flag[i-1][j]++;
                if(i+1<vec.size())
                    flag[i+1][j]++;
                if(j-1>=0)
                    flag[i][j-1]++;
                if(j+1<vec.size())
                    flag[i][j+1]++;
                if(i-1>=0&&j-1>=0)
                    flag[i-1][j-1]++;
                if(i-1>=0&&j+1<vec.size())
                    flag[i-1][j+1]++;
                if(i+1<=vec.size()&&j-1>=0)
                    flag[i+1][j-1]++;
                if(i+1<=vec.size()&&j+1<vec.size())
                    flag[i+1][j+1]++;
            }
        }
    }
    
}



int main()
{
    ifstream ifs("test");
    if(!ifs.is_opend())
    {
        return 0;
    }
    
    int num;
    ifs>>num;
    for(int i=0; i<num; i++)
    {
        int n;
        ifs>>n;
        string str;
        vector<string> svec;
        for(int i=0; i<n; i++)
        {
            ifs>>str;
            svec.push_back(str);
        }
        vector<string> flag(svec.size(), string(svec.size, 0));
    }
}



