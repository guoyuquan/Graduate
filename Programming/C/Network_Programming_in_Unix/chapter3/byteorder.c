#include <stdio.h>

union
{
    short s;
    char a[sizeof(short)];
}test;

int
main()
{
    test.s=0x0102;
    printf("%s\n", CPU_VENDOR_OS);
    if(test.a[0]==1&&test.a[1]==2)
    {
        printf("big endian\n");
    }
    else
        printf("little endian\n");
    return 0;
}