#include<stdio.h>
struct nlist{
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

unsigned _hash(char *s)
{
    unsigned hashval;
    
    for(hashval=0; *s !='\0'; s++)
        hashval=*s+31*hashval;
    return hashval%HASHSIZE;
}

#include<string.h>
struct nlist *lookup(char *s)
{
    struct nlist *np;
    //printf("%s\n", s);
    //printf("%d\n", _hash(s));
    for(np=hashtab[_hash(s)]; np!=NULL; np=np->next)
        if(strcmp(s,np->name)==0)
            return np;
    return NULL;
}

#include<stdlib.h>

char *_strdup(char *);

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if((np=lookup(name))==NULL)
    {
        np=(struct nlist *)malloc(sizeof(*np));
        if(np==NULL||(np->name=_strdup(name))==NULL)
            return NULL;
        hashval=_hash(name);
        np->next=hashtab[hashval];
        hashtab[hashval]=np;
    }
    else
        free((void *)np->defn);
    if((np->defn=_strdup(defn))==NULL)
        return NULL;
    return np;
}

char *_strdup(char *s)
{
    char *p=(char *)malloc(strlen(s)+1);
    if(p!=NULL)
        strcpy(p,s);
    return p;
    
}

int undef(char *name)
{
    struct nlist *np=lookup(name);
    if(np==NULL)
        return 0;
    unsigned val=_hash(name);
    struct nlist *temp=hashtab[val];
    if(strcmp(temp->name,name)==0)
    {
        hashtab[val]=temp->next;
        goto find;
    }
    for(temp=hashtab[val]->next;strcmp(temp->next->name,name)!=0;temp=temp->next)
        ;
    temp->next=np->next;
find:
    free((void *)np->name);
    free((void *)np->defn);
    free((void *)np);
    return 1;
}

#include<ctype.h>
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

#include<string.h>
int main()
{
    char name[32];
    char defn[32];
    struct nlist *np;
    while(getword(name,32)!=EOF&&getword(defn,32)!=EOF)
    {
        install(name, defn);
        np=lookup(name);
        if(np==NULL)
        {
            printf("np==NULL\n");
            return 0;
        }
        printf("%s %s ", np->name, np->defn);
        printf("%d\n", undef(np->name));
    }
    return 0;
}