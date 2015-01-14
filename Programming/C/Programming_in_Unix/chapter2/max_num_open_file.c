#include<stdio.h>
#include<sys/param.h>
#include<unistd.h>

int main()
{
    printf("* opened files number: %d\n", NOFILE);
    for(int i=0; i<NOFILE+0; i++)
    {
        printf("%d ", i);
        close(i);
    }
    printf("opened files number:%d\n", NOFILE);
    return 0;
}