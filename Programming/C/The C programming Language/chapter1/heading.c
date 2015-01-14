#include<stdio.h>

int main()
{
    float fhabr, celsius;
    float lower, upper, step;
    lower=0;
    upper=300;
    step=20;
    fhabr=lower;
    printf("This is a temperature converting table:\n");
    while(fhabr<=upper)
    {
        celsius=(5.0/9.0)*(fhabr-32.0);
        printf("%3.0f %8.2f\n",fhabr, celsius);
        fhabr=fhabr+step;
    }
}