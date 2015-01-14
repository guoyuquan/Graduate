#include<stdio.h>

#define IN   0
#define OUT  1

int main()
{
    int c;
    int state;
    state=OUT;
    while((c=getchar())!=EOF)
    {
        if(c=='\t'||c==' '||c=='\n')
        {
            if(state==OUT);
            else
            {
                state=IN;
                printf("\n");
            }
        }
        else
        {
            putchar(c);
            state=IN;
        }
        
    }
}