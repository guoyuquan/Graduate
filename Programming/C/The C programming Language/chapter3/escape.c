#include<stdio.h>

void escape(char s[], char t[]);
void rescape(char s[], char t[]);
int main()
{
    char s[10];
    char t[20];
    char c;
    int i=0;
    while((c=getchar())!=EOF)
    {
        s[i]=c;
        i++;
    }
    escape(s,t);
    printf("%s\n", t);
    rescape(s,t);
    printf("%s\n", t);
    return 0;
}
void escape(char s[], char t[])
{
    int i,k=0;
    for(i=0;s[i]!='\0';++i,++k)
    {
        switch(s[i])
        {
            case '\n' :
            case '\t' :
                for(int j=0;j<6;++j)
                    t[k++]=' ';
                break;
            default:
                t[k]=s[i];
                break;
        }
    }
    t[k]='\0';
}


void rescape(char s[], char t[])
{
    int i, k=0;
    for(i=0;s[i]!='\0';++i,++k)
    {
        switch(s[i])
        {
            case ' ' :
                for(int j=0;s[i+j]!='\0'&&j<6&&s[i+j]==' ';++j)
                    if(j==5)
                    {
                        t[k]='\t';
                        i+=5;
                    }
                break;
            default :
                t[k]=s[i];
                break;
        }
    }
    t[k]='\0';
}
