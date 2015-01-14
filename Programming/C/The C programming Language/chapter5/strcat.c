#include<stdio.h>

void _strcat(char *s, char *t);

int main()
{
    char s[32]="ZHANG";
    char t[]=" QIU CHEN";
    _strcat(s,t);
    printf("%s\n",s);
    return 0;
}

void _strcat(char *s, char *t)
{
    while(*s)
        s++;
    while(*s++=*t++)
        ;
}