#include<stdio.h>

#define MAX 1000

int main()
{
    char input[MAX];
    for(int i=0;(input[i]=getchar())!=EOF;++i)
    {
        if(input[i]=='\t')
        {
            input[i]=' ';
            int j=1;
            for(i=i+j;j<6;++j)
                input[i]=' ';
        }
        
    }
    printf("%s\n",input);
}