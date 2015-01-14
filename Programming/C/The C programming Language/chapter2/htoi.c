#include<stdio.h>

#define MAX 1000
int main()
{
    char s[MAX];
    int ch;
    int i=0;
    while((ch=getchar())!=EOF&&ch!='\n')
    {
        s[i]=ch;
        ++i;
    }
    s[i]='\0';
    int n=0;
    int flag=0;
    for(i=0;s[i]!='\0';++i)
    {
        
        if(s[0]=='0'&&(s[1]=='x'||s[1]=='X')&&flag==0)
        {
            i=2;
        }
        flag=0;
        
        if(s[i]>='0'&&s[i]<='9')
        {
            n=n*16+(s[i]-'0');
            flag=1;
        }
        if(s[i]>='a'&&s[i]<='f')
        {
            n=n*16+(s[i]-'a'+10);
            flag=1;
        }
        if(s[i]>='A'&&s[i]<='F')
        {
            n=n*16+(s[i]-'A'+10);
            flag=1;
        }
        if(flag!=1)
        {
            printf("ERROR:Invalid input.\n");
        }
    }
    printf("Input is: %s\n",s);
    printf("The corresponding integer is: %d\n",n);
    return 0;
}