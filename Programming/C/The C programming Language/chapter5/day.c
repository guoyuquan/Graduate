#include<stdio.h>

static char daytab[2][13]={
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
    int i, m, d;
    printf("%d\n",i=day_of_year(2016, 12, 16));
    month_day(2016,i,&m,&d);
    printf("%d %d\n",m,d);
    return 0;
}

int day_of_year(int year, int month, int day)
{
    int i, leap;
    if(year<0)
    {
        printf("error: invalid year\n");
        return 0;
    }
    if(month>12||month<1)
    {
        printf("error:invalid month\n");
        return 0;
    }
    leap=(year%4==0&&year%100!=0)||year%400==0;
    if(leap)
    {
        if(day<1||day>366)
        {
            printf("error: invalid day\n");
            return 0;
        }
    }
    else
    {
        if(day<1||day>365)
        {
            printf("error: invalid day\n");
            return 0;
        }
    }
    for(i=1;i<month;i++)
        day+=daytab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    if(year<0)
    {
        printf("error: invalid year\n");
        return;
    }
    leap=(year%4==0&&year%100!=0)||year%400==0;
    if(leap)
    {
        if(yearday<1||yearday>366)
        {
            printf("error: invalid day\n");
            return;
        }
    }
    else
    {
        if(yearday<1||yearday>365)
        {
            printf("error: invalid day\n");
            return;
        }
    }
    for(i=1;yearday>daytab[leap][i];i++)
        yearday-=daytab[leap][i];
    *pmonth=i;
    *pday=yearday;
}