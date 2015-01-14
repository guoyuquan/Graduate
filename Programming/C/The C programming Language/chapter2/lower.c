#include<stdio.h>

void lower(char str[]);
int main()
{
    char str[100];
    int ch,i=0;
    while((ch=getchar())!=EOF)
    {
        str[i++]=ch;
    }
    str[i]='\0';
    lower(str);
    printf("%s\n",str);
}

void lower(char str[])
{
    for(int i=0;str[i]!=0;++i)
    {
        str[i]=str[i]>='A'&&str[i]<='Z'?str[i]-('A'-'a'):str[i];
    }
}