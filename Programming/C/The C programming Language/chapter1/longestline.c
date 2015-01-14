#include<stdio.h>

#define MAXLINE 1000

int getLine(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    int cnt,max;
    char line[MAXLINE];
    char newLine[MAXLINE];
    max=0;
    while((cnt=getLine(newLine,MAXLINE))>0)
          {
              if(cnt>max)
              {
                  max=cnt;
                  copy(line,newLine);
              }
          }
    if(max>0)
          printf("%s\n", line);
          return 0;
}

int getLine(char line[],int maxline)
{
    int i=0;
    char c=getchar();
    while(c!='\n'&&i<maxline&&c!=EOF)
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