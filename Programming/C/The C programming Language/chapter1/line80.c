#include<stdio.h>

#define MAXLINE 1000

int getLine(char line[], int n);
void copy(char to[], char from[]);

int main()
{
    int cnt;
    char line[MAXLINE];
    while((cnt=getLine(line,MAXLINE))>0)
    {
        if(cnt>80)
            printf("%s\n",line);
    }
}

int getLine(char line[], int n)
{
    int i=0;
    char c;
    c=getchar();
    while(c!='\n'&&i!=n&&c!=EOF)
    {
        line[i]=c;
        c=getchar();
        ++i;
    }
    return i;
}

void copy(char to[], char from[])
{
    for(int i=0;from[i]!='\0';++i)
        to[i]=from[i];
}