#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("%d\n", _SC_OPEN_MAX);
    for(int i=0; i<sysconf(_SC_OPEN_MAX); i++)
        close(i);
}
