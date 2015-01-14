#include<stdio.h>
#include<ctype.h>

int getch(void);
void ungetch(int);
double getfloat(double *dp);

int main()
{
    double p;
    getfloat(&p);
    printf("%.6g\n",p);
    return 0;
}

char _ch;
int bufp=0;

int getch(void)
{
    if(bufp>0)
    {
        bufp--;
        return _ch;
    }
    return getchar();
}

void ungetch(int c)
{
    bufp++;
    _ch=c;
}

double getfloat(double *dp)
{
    int c, sign;
    double power=1.0;
    while(isspace(c=getch()))
        ;
    if(c!=EOF&&c!='+'&&c!='-'&&!isdigit(c))
    {
        ungetch(c);
        return 0;
    }
    sign=(c=='-')?-1:1;
    if(isdigit(c))
        ungetch(c);
    for(*dp=0.0;isdigit(c=getch());)
    {
        *dp=10.0**dp+(c-'0');
    }
    if(c=='.')
        for(power=1.0;isdigit(c=getch());)
        {
            *dp=10.0**dp+(c-'0');
            power*=10.0;
        }
    *dp=*dp/power*sign;
    if(c!=EOF)
        ungetch(c);
    return c;
}

