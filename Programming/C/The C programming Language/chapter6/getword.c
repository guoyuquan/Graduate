#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int getword(char *word, int lim);

int main()
{
    char word[100];
    while(getword(word, 100)!=EOF)
        printf("%s\n",word);
    return 0;
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w=word;
    
    while (isspace(c=getch()))
        ;
    if(c!=EOF)
        *w++=c;
    if(!isalpha(c))
    {
        if(c=='_'&&isalpha(*w++=getch()))
        {
            ungetch(*--w);
            goto alpha;
        }
        if(c=='\"'&&isalpha(*w++=getch()))
        {
            ungetch(*--w);
            goto alpha;
        }
        if(c=='/'&&(*w++=getch())=='/')
        {
            if(isalpha(*w++=getch()))
                goto alpha;
            ungetch(*--w);
            ungetch('/');
        }
        if(c=='/'&&(*w++=c=getch())=='*')
        {
            if(isalpha(*w++=getch()))
                goto alpha;
            ungetch(*--w);
            ungetch('*');
        }
        if(c=='#'&&isalpha(*w++=getch()))
        {
            ungetch(*--w);
            goto alpha;
        }
        *w='\0';
        return c;
    }
alpha:
    for(;--lim>0&&isalnum(*w++=c=getch());)
        ;
    if(c=='\"')
    {
        *w='\0';
        return word[0];
    }
    if(c=='*'&&(*w++=getch())=='/')
    {
        *w='\0';
        return word[0];
    }
    *--w='\0';
    return word[0];
}

int ch[5];
int flag=0;

int getch(void)
{
    return flag>0?ch[--flag]:getchar();
}

void ungetch(int c)
{
    ch[flag++]=c;
}