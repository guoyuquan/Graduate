#include<stdio.h>

#define MAXLENGTH 45
#define IN  0
#define OUT 1

int main()
{
    int c,i,flag,len;
    int counter[MAXLENGTH];
    for(i=0;i<MAXLENGTH;++i)
        counter[i]=0;
    flag=OUT;
    for(i=0;(c=getchar())!=EOF;)
    {
        if(c==' '||c=='\n'||c=='\t')
        {
            if(flag==IN)
            {
                flag=OUT;
                ++counter[i];
                i=0;
            }
        }
        else
        {
            flag=IN;
            ++i;
        }
    }
    int max=0;
    for(i=0;i<MAXLENGTH;++i)
    {
        printf("length %d:",i);
        for(int j=0;j<counter[i];++j)
            putchar('*');
        printf("\n");
        if(max<counter[i])
            max=counter[i];
    }
    int min=0;
    for(i=0;i<MAXLENGTH;++i)
    {
        counter[i]=counter[i]-max;
        if(min>counter[i])
            min=counter[i];
    }
    printf("\n");
    while(min!=0)
    {
        for(i=0;i<MAXLENGTH;++i)
        {
            if(counter[i]>=0)
                putchar('*');
            else
                putchar(' ');
            ++counter[i];
        }
        ++min;
    }
}