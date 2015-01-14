#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name[L_tmpnam], line[100];
    FILE *fp;
    printf("%s\n", tmpnam(NULL));
    tmpnam(name);
    printf("%s\n", name);
    if((fp=tmpfile())==NULL)
    {
        fprintf(stderr, "error: tmpfile\n");
        exit(0);
    }
    fputs("one line of output\n", fp);
    rewind(fp);
    if(fgets(line, sizeof(line), fp)==NULL)
    {
        fprintf(stderr, "error: fgets\n");
        exit(0);
    }
    fputs(line, stdout);
    return 0;
}