#include<stdio.h>

#define MAXLINE  1000

int getLine(char line[],int n);
void reverse(char src[], int cnt);
int main()
{
    char input[MAXLINE];
    int cnt;
    while((cnt=getLine(input,MAXLINE))>0)
    {
        reverse(input,cnt);
        printf("%d\n",cnt);
        printf("%s\n",input);
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
    line[i]='\0';
    return i;
}

void reverse(char src[], int cnt)
{
    char tmp;
    for(int i=0;i<=(cnt-1)/2;++i)
    {
        tmp=src[i];
        src[i]=src[cnt-1-i];
        src[cnt-1-i]=tmp;
        printf("%d %d\n",i, cnt-i-1);
    }
        
}