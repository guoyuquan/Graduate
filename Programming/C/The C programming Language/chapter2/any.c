#include<stdio.h>

#define MAX 100

int any(char a[], char b[]);

int main()
{
    int ch, i=0;
    char s1[MAX],s2[MAX];
    for(i=0;(ch=getchar())!='\n';++i)
        s1[i]=ch;
    s1[i]='\0';
    for(i=0;(ch=getchar())!='\n';++i)
        s2[i]=ch;
    s2[i]='\n';
    printf("%s \n %s \n",s1,s2);
    printf("%d\n",any(s1,s2));
}

int any(char a[], char b[])
{
    int i=0;
    int flag=0;
    while(a[i]!='\0')
    {
        for(int j=0;b[j]!='\0';++j)
            if(a[i]==b[j])
            {
                flag=1;
                break;
            }
        ++i;
        if(flag)
            break;
    }
    return i;
}