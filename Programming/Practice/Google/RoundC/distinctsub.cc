#include <iostream>
#include <string>

int numDistinct(std::string S, std::string T) {
        if(S.size()<T.size())
        return 0;
        if(S==T)
        return 1;
        int *arr=new int [T.size()+1];
        arr[0]=1;
        for(int i=1; i<T.size()+1; i++)
        arr[i]=0;
        for(int i=0; i<S.size(); i++)
        {
            for(int j=T.size()-1; j>=0; j--)
                if(S[i]==T[j])
                    arr[j+1]+=arr[j];
            for(int k=0; k<=T.size(); k++)
                std::cout<<arr[k]<<" ";
            std::cout<<std::endl;
        }
        return arr[T.size()];
        
    }
int main()
{
numDistinct("rabbbit", "rabbit");
}
