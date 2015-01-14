#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void my_exit1(void);
void my_exit2(void);

int main()
{
    if(atexit(my_exit2)!=0)
    {
        fprintf(stderr, "error: register, atexit\n");
        return 0;
    }
    if(atexit(my_exit1)!=0)
    {
        fprintf(stderr, "error: register, atexit\n");
        return 0;
    }
    if(atexit(my_exit1)!=0)
    {
        fprintf(stderr, "error: register, atexit\n");
        return 0;
    }
    printf("main is done\n");
    return 0;
}

void my_exit1()
{
    printf("first exit handler\n");
}

void my_exit2()
{
    printf("second exit handler\n");
}