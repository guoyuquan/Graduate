#include <stdio.h>

struct fun{
    int i;
};

int fun()
{
    printf("just a test\n");
    return 0;
}
int main()
{
    struct fun s;
    fun();
}