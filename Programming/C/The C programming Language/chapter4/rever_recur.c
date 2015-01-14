#include<stdio.h>
#include<string.h>

void reverse(char s[]);
int main()
{
    char s[]="ZHANG QIU CHEN";
    reverse(s);
    printf("%s\n", s);
    return 0;
}

void reverse(char s[])
{
    static int i=0;
    int j=strlen(s)-1;
    char temp;
    temp=s[i];
    s[i]=s[j-i];
    s[j-i]=temp;
    i++;
    if(i<j-i)
        reverse(s);
}