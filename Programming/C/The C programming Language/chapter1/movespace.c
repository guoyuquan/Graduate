#include<stdio.h>

#define MAXLINE 1000

int getLine(char input[], int n);
void copy(char to[], char from[]);

int main()
{
    char input[MAXLINE];
    int cnt;
    while((cnt=getLine(input, MAXLINE))>0)
    {
        for(int i=cnt-1;i>=0;--i)
        {
            if(input[i]==' '||input[i]=='\n'||input[i]=='\t')
                input[i]='\0';
        }
        printf("%s",input);
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