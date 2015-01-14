#include<stdio.h>
#include<string.h>

void itob(int n, char s[], int b);

int main()
{
    int i=-2147483648;
    char s[36];
    itob(i, s, 2);
    printf("%s\n", s);
    itob(i, s, 3);
    printf("%s\n", s);
    itob(i, s, 8);
    printf("%s\n",s);
    itob(i, s, 10);
    printf("%s\n",s);
    itob(i, s, 16);
    printf("%s\n",s);
    return 0;
}

void itob(int n, char s[], int b)
{
    if(b<=1||b>35)
    {
        printf("Bad Base\n");
        return;
    }
    int sign, i, div, flag=0;
    i=0;
    if((sign=n)<0)
    {
        if(n>-2147483648)
            n=-n;
        else
        {
            n=-(n+1);
            flag=1;
        }
    }
    if(b<=10)
    {
        do{
            s[i++]=n%b+'0';
        }while((n/=b)>0);
    }
    else
    {
        do{
            div=n%b;
            if(div<=9)
            {
                s[i++]=div+'0';
            }
            else
                s[i++]=div-10+'a';
        }while((n/=b)>0);
    }
    if(sign<0)
    {
        if(flag)
        {
            if(s[0]!=('0'+b-1)&&s[0]!=('a'+b-11))
            {
                s[0]++;
            }
            else
            {
                for(int j=0;j<i;j++)
                {
                    if(s[j]==('0'+b-1)||s[j]==('a'+b-11))
                        s[j]='0';
                    else
                    {
                        flag=0;
                        s[j]++;
                        break;
                    }
                }
                if(flag)
                    s[i++]='1';
            }
        }
        s[i++]='-';
    }
    s[i]='\0';
    char temp;
    for(int j=0, k=strlen(s)-1;j<k;j++,k--)
    {
        temp=s[j];
        s[j]=s[k];
        s[k]=temp;
    }
}