#include<stdio.h>

void expand (char *s1, char *s2);
int main()
{
    char s1[20];
    char s2[100];
    int i=0;
    char c;
    while((c=getchar())!=EOF)
    {
        s1[i]=c;
        ++i;
    }
    expand(s1, s2);
    printf("%s%s", s1, s2);
    return 0;
}

void expand(char *s1, char *s2)
{
    int i, j, k;
    i=j=k=0;
    for(i=0;s1[i]!='\0';++i)
    {
        switch(s1[i])
        {
            case '-' :
            {
                if(i>0&&s1[i+1]!='\0')
                {
                    if(s1[i-1]>='a'&&s1[i-1]<'z'&&s1[i+1]>='a'&&s1[i+1]<='z')
                    {
                        for(char c=s1[i-1]+1;c<s1[i+1];++c)
                        {
                            s2[j++]=c;
                        }
                        //++i;
                    }
                    else if(s1[i-1]>='A'&&s1[i-1]<'Z'&&s1[i+1]>='A'&&s1[i+1]<='Z')
                    {
                        for(char c=s1[i-1]+1;c<s1[i+1];++c)
                            s2[j++]=c;
                        //++i;
                    }
                    else if(s1[i-1]>='0'&&s1[i-1]<'9'&&s1[i+1]>='0'&&s1[i+1]<='9')
                    {
                        for(char c=s1[i-1]+1;c<s1[i+1];++c)
                            s2[j++]=c;
                        //++i;
                    }
                }
                break;
            }
            default:
                s2[j++]=s1[i];
                break;
        }
    }
    s2[j]='\0';
}