#include<stdio.h>
#include<string.h>

int _strend(char *s, char *t);

int main()
{
    char *s="ZHANG QIU CHEN";
    char *t="CHEN";
    printf("%s\n%s\n%d\n",s,t,_strend(s,t));
    return 0;
}

int _strend(char *s, char *t)
{
    s=s+strlen(s)-strlen(t);
    for(;*s++==*t++;)
        if(*s=='\0')
            return 1;
    return 0;
}