#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

struct tnode{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

int main()
{
    struct tnode *root;
    char word[MAXWORD];
    root=NULL;
    while(getword(word, MAXWORD)!=EOF)
        if(isalpha(word[0]))
            root=addtree(root, word);
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char * _strdup(char *);

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if(p==NULL)
    {
        p=talloc();
        p->word=_strdup(w);
        p->count=1;
        p->left=p->right=NULL;
    }
    else if((cond=strcmp(w, p->word))==0)
        p->count++;
    else if(cond<0)
        p->left=addtree(p->left, w);
    else
        p->right=addtree(p->right, w);
    return p;
}

void treeprint(struct tnode *p)
{
    if(p!=NULL)
    {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

#include<stdlib.h>

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

char *_strdup(char *s)
{
    char *p;
    p=(char *)malloc(strlen(s)+1);
    if(p!=NULL)
        strcpy(p,s);
    return p;
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