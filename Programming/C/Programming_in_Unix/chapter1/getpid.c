#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("hello world from process: %d\n", getpid());
    return 0;
}