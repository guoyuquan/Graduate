#include<stdio.h>
#include<string.h>
#define MAX 1000

int strindex(char source[], char target[]);

int main()
{
    char s[]="Zhang Qiu Chen Zhang Qiu chen";
    char t[]="Qiu";
    printf("%d\n",strindex(s,t));
    return 0;
}

int strindex(char s[], char t[])
{
    int i, j, k;
    for(i=strlen(s)-1;i>=0;--i)
    {
        for(j=i,k=0;t[k]!='\0'&&s[j]==t[k];k++,j++)
            ;
        if(k>0&&t[k]=='\0')
            return i;
    }
    return -1;
}