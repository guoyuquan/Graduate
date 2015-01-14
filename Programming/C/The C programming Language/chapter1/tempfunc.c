#include<stdio.h>

#define STEP 20
#define DIFF 32

float temperature(float fahr);
int main()
{
    for(int i=0;i<=300;i+=STEP)
        printf("%3d %6.1f\n", i, temperature(i));
}

float temperature(float fahr)
{
    return (5.0/9.0)*(fahr-32);
}