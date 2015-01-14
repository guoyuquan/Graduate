#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int filecmp(char *, char *);

int main(int argc, char * argv[])
{
    if(argc<3)
    {
        printf("error: need two file name\n");
        exit(1);
    }
    filecmp(argv[1], argv[2]);
    return 0;
}

int filecmp(char * file1, char * file2)
{
    FILE *fp1, *fp2;
    if((fp1=fopen(file1, "r"))==NULL)
    {
        fprintf(stdout,"error: open %s\n", file1);
        exit(1);
    }
    if((fp2=fopen(file2, "r"))==NULL)
    {
        fprintf(stdout, "error: open %s", file2);
        exit(1);
    }
    char line1[100], line2[100];
    while(fgets(line1, 100, fp1)!=NULL && fgets(line2, 100, fp2)!=NULL)
    {
        if(strcmp(line1, line2)==0)
            continue;
        else
        {
            fprintf(stdout, "%s%s", line1, line2);
            fclose(fp1);
            fclose(fp2);
            return 1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}