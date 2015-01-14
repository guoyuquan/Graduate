#include<stdio.h>

void strcpy_n(char *s, char *t, int n);
void strcat_n(char *s, char *t, int n);
int strcmp_n(char *s, char *t, int n);

int main()
{
    char s[32]="ZHANG QIU CHEN";
    char *t="CHEN";
    char str[32];
    printf("%d\n",strcmp_n(s, t, 3));
    strcat_n(s, t, 3);
    printf("%s\n", s);
    strcpy_n(str,s,5);
    printf("%s\n", str);
    return 0;
}

void strcat_n(char *s, char *t, int n)
{
    while(*s!='\0')
        s++;
    for(int i=0;i<n&&(*s++=*(t+i))!='\0';i++)
        ;
}

void strcpy_n(char *s, char *t, int n)
{
    for(int i=0;i<n&&(*s++=*(t+i))!='\0';i++)
        ;
    *s='\0';
}

int strcmp_n(char *s, char *t, int n)
{
    int i=0;
    for(i=0;i<n&&*(s+i)==*(t+i);i++)
        if(*s=='\0')
            return 0;
    return *s-*t;
}