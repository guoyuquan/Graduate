#include<stdio.h>
#include<stdarg.h>

void minscanf(char *fmt, ...);

int main()
{
    int i;
    double d;
    char s[20];
    minscanf("%d/%f/%s", &i, &d, s);
    printf("%d %f %s\n", i, d, s);
    return 0;
}

void minscanf(char *fmt, ...)
{
    va_list ap;
    int * ival;
    double * dval;
    char * sval, *p;
    va_start(ap, fmt);
    for(p=fmt; *p!='\0'; p++)
    {
        if(*p!='%')
        {
            getchar();
            continue;
        }
        switch(*++p)
        {
            case 'd' :
                ival=va_arg(ap, int *);
                scanf("%d", ival);
                break;
            case 'f' :
                dval=va_arg(ap, double *);
                scanf("%lf", dval);
                break;
            case 's' :
                sval=va_arg(ap, char *);
                scanf("%s", sval);
                break;
            default:
                getchar();
                break;
        }
    }
    va_end(ap);
}