#include<stdio.h>
#include<string.h>

void itoa(int n, char s[]);
int main()
{
    int i=-2147483648;
    char s[36];
    itoa(i, s);
    printf("%s\n",s);
    return 0;
}

void itoa(int n, char s[])
{
    int i, sign, flag;
    flag=0;
    if((sign=n)<0)
    {
        if(n>-2147483648)
            n=-n;
        else
        {
            n=-(n+1);
            flag=1;
        }
    }
    i=0;
    do
    {
        s[i++]=n%10+'0';
    }while((n/=10)>0);
    if(sign<0)
    {
        s[i++]='-';
        if(flag)
            s[0]+=1;
    }
    s[i]='\0';
    char temp;
    for(int j=0,k=strlen(s)-1;j<k;j++,k--)
    {
        temp=s[j];
        s[j]=s[k];
        s[k]=temp;
    }
}