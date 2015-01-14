#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

static void f1(int, int ,int ,int);
static void f2();

static jmp_buf jmpbuffer;
static int globval=1;

int main()
{
    int autoval=2;
    register int regival=3;
    volatile int volaval=4;
    static int statval=5;
    if(setjmp(jmpbuffer)!=0)
    {
        printf("after longjmp:\n");
        printf("gloabal value=%d, auto=%d, register=%d, volatile=%d, static=%d\n",globval, autoval, regival, volaval, statval);
        exit(0);
    }
    
    globval=95; autoval=96; regival=97; volaval=98; statval=99;
    f1(autoval, regival, volaval, statval);
    exit(0);
}

static void f1(int i, int j, int k, int l)
{
    printf("in f1(): \n");
    printf("global=%d, auto =%d, register = %d, volatile = %d, static = %d\n", globval, i, j, k, l);
    f2();
}

static void f2()
{
    longjmp (jmpbuffer, 1);
}