#include<stdio.h>
#include<ctype.h>

double atof(char source[]);

int main()
{
    //double atof(char s[]);
    char s[]="-12.6666";
    printf("%6.4f\n", atof(s));
        return 0;
}

double atof(char s[])
{
    double val, power;
    int i, sign;
    for(i=0;isspace(s[i]);i++)
        ;
    sign=(s[i]=='-')?-1:1;
    if(s[i]=='-'||s[i]=='+')
        i++;
    for(val=0.0; isdigit(s[i]);i++)
        val=10.0*val+(s[i]-'0');
    if(s[i]=='.')
        i++;
    for(power=1.0;isdigit(s[i]);i++)
    {
        val=10.0*val+(s[i]-'0');
        power*=10;
    }
    return sign*val/power;
}