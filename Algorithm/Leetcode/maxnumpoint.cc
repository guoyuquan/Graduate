#include<iostream>
#include<vector>
using std::cout;
using std::cin;
using std::endl;
using std::vector;

struct Point{
    int x;
    int y;
    Point():x(0),y(0){}
    Point(int a,int b):x(a),y(b){}
};

int main()
{
    vector<Point> points;
    int a,b;
    while(cin>>a>>b)
    {
        Point p(a,b);
        points.push_back(p);
    }
    int n=points.size();
    if(n<=2)
    {
        cout<<n<<endl;
        return n;
    }
    vector<double> k;
    int res=0,dup=1;
    for(int i=0;i<n;++i)
    {
        k.clear();
        dup=1;
        for(int j=0;j<n;++j)
        {
            if(points[i].x-points[j].x==0)
            {
                if(points[i].y-points[j].y==0)
                {
                    ++dup;
                }
                else
                    k.push_back(99999);
            }
            else
                k.push_back(10000*(points[i].y-points[j].y)/(points[i].x-points[j].x));
        }
    }
    sort(k.begin(),k.end());
    int pp=1;
    if(k.size()==0)
        pp=0;
    for(int j=1;j<k.size();++j)
    {
        if(k[j]==k[j-1])
            ++pp;
        else
        {
            if(pp+dup>res)
                res=pp+dup;
            pp=1;
        }
    }
    if(pp+dup>res)
        res=pp+dup;
    cout<<res<<endl;
    return res;
}