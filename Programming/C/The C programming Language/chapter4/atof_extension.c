#include<stdio.h>
#include<stdlib.h>

double _atof(char source[]);
int main()
{
    char s1[]="-12.6666";
    char s2[]="12.6666e-3";
    char s3[]="12.6666e6";
    printf("%s\n%6.4f\n%s\n%6.4f\n%s\n%6.4f\n",s1,_atof(s1),s2,_atof(s2),s3,_atof(s3));
    return 0;
}

double _atof(char s[])
{
    int i, sign=1;
    for(i=0;s[i]==' '||s[i]=='\t'||s[i]=='\n';i++)
        ;
    if(s[i]=='+'||s[i]=='-')
    {
        sign=(s[i]=='-')?-1:1;
        i++;
    }
    if((s[i]<'0'||s[i]>'9')&&s[i]!='.')
    {
        printf("Bad String: fail to parse %s\n", s);
        exit(1);
    }
    double val, power;
    for(val=0.0;s[i]>='0'&&s[i]<='9';++i)
        val=10.0*val+(s[i]-'0');
    if(s[i]=='.'||s[i]=='e'||s[i]=='E')
        ++i;
    else
    {
        printf("Bad String: fail to parse %s\n",s);
        exit(1);
    }
    for(power=1.0;s[i]>='0'&&s[i]<='9';++i)
    {
        val=10.0*val+(s[i]-'0');
        power*=10;
    }
    val*=sign;
    if(s[i]=='\0')
        return val/power;
    else if(s[i]=='e'||s[i]=='E')
    {
        i++;
        sign=1;
        if(s[i]=='-'||s[i]=='+')
        {
            sign=(s[i]=='-')?-1:1;
            ++i;
        }
        if(s[i]>='0'&&s[i]<='9')
        {
            int j=0, i_pw=0;
            for(;s[i]>='0'&&s[i]<='9';++i)
                i_pw=10*i_pw+(s[i]-'0');
            if(s[i]=='\0')
            {
                for(j=0;j<i_pw;++j)
                {
                    if(sign==1)
                        power/=10;
                    else
                        power*=10;
                }
                return val/power;
            }
            printf("Bad String: fail to parse %s\n",s);
            exit(1);
        }
        printf("Bad String: fail to parse %s\n",s);
        exit(1);
    }
    printf("Bad String: fail to parse %s\n",s);
    exit(1);
}