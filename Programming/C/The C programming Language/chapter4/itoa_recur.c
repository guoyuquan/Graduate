#include<stdio.h>

int itoa(char t[], int n);

int main()
{
    char t[32];
    int n=-289767;
    itoa(t, n);
    printf("%s\n",t);
    return 0;
}

int itoa(char t[], int n)
{
    int i=1, flag=0;
    if(n<0)
    {
        n=-n;
        flag=1;
    }
    if(n/10)
        i=itoa(t,n/10);
    t[i++]=n%10+'0';
    if(flag)
        t[0]='-';
    else
        t[0]='+';
    t[i]='\0';
    return i;
}