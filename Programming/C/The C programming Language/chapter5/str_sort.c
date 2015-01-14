#include<stdio.h>
#include<string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main()
{
    int nlines;
    if((nlines=readlines(lineptr, MAXLINES))>=0)
    {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("error: inut too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000

int _getline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    
    nlines=0;
    while((len=_getline(line, MAXLEN))>0)
        if(nlines>=maxlines||(p=alloc(len))==NULL)
            return -1;
        else
        {
            line[len-1]='\0';
            strcpy(p,line);
            lineptr[nlines++]=p;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    while(nlines-->0)
        printf("%s\n",*lineptr++);
}

int _getline(char *s, int n)
{
    int i=1;
    char c;
    while(i<n&&(*s++=c=getchar())!=EOF&&c!='\n')
        i++;
    if(c==EOF)
        return 0;
    *s='\0';
    return i;
}


void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    if(left>=right)
        return;
    swap(v, left, (left+right)/2);
    last=left;
    for(i=left+1;i<=right;i++)
        if(strcmp(v[i],v[left])<0)
            swap(v, ++last, i);
    swap(v,left, last);
    qsort(v, left, last-1);
    qsort(v,last+1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;
    temp=v[i];
    v[i]=v[j];
    v[j]=temp;
}

char mem[5000];
char * bufp=mem;
char * alloc(int n)
{
    char *p=bufp;
    if(bufp-mem+n>5000)
        return 0;
    bufp+=n;
    return p;
}