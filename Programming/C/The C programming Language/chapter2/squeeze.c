#include<stdio.h>

#define MAX 100

void squeeze(char s1[], char s2[]);

int main()
{
    char ch, s1[MAX],s2[MAX];
    int i=0;
    while((ch=getchar())!='\n')
    {
        s1[i++]=ch;
    }
    s1[i]='\0';
    i=0;
    while((ch=getchar())!='\n')
    {
        s2[i++]=ch;
    }
    s2[i]='\0';
    printf("%s \n%s\n",s1,s2);
    squeeze(s1,s2);
    printf("%s\n",s1);
}

void squeeze(char s1[],char s2[])
{
    int i=0,k=0;
    while(s1[i]!='\0')
    {
        int j=0;
        int flag=0;
        while(s2[j]!='\0')
        {
            if(s1[i]==s2[j++])
                flag=1;
        }
        if(!flag)
            s1[k++]=s1[i];
        ++i;
    }
    s1[k]='\0';
}