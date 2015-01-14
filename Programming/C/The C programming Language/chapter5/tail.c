#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int _getline(char *s);
int main(int argc, char **argv)
{
    int n=10, temp;
    if(argc>1)
    {
        temp=atof(*(argv+1)+1);
        if(temp==0)
            return 0;
        n=temp;
    }
    char * text[36];
    char line[1000];
    char *p=line;
    int i=0;
    char c;
    while((c=_getline(p))!=EOF&&i<35)
    {
        text[i++]=p;
        p=p+strlen(p);
    }
    text[i]=NULL;
    i=(i-n)<0?0:i-n;
    for(int j=0;j<n&&text[j]!=NULL;j++)
    {
        printf("%d:%s\n", j+1, text[i++]);
    }
    return 0;
}

int _getline(char *s)
{
    char c;
    while((c=getchar())!=EOF&&c!='\n')
        *s++=c;
    *s='\0';
    return c;
}