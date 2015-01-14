#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void find_pattern(char *, char *);

int main(int argc, char *argv[])
{
    char pattern[20];
    char file[20];
    if(argc<3)
    {
        fprintf(stdout, "not exact arguments, please enter in\n");
        fprintf(stdout, "Please enter pattern to be found:");
        fscanf(stdin, "%s", pattern);
        fprintf(stdout, "please enter file name:");
        fscanf(stdin, "%s", file);
    }
    else
    {
        strcpy(pattern,argv[1]);
        strcpy(file, argv[2]);
    }
    find_pattern(pattern, file);
    return 0;
}

void find_pattern(char *pattern, char *file)
{
    char line[100];
    int lineno=0;
    FILE *fp;
    if((fp=fopen(file, "r"))==NULL)
    {
        fprintf(stdout, "error: open file %s\n", file);
        exit(1);
    }
    while(fgets(line, 100, fp)!=NULL)
    {
        lineno++;
        for(int i=0; *(line+i)!='\0'; i++)
            if(*(line+i)==*pattern)
            {
                int k;
                for(k=0; *(line+i+k)!='\0'&&*(pattern+k)==*(line+i+k);k++)
                    ;
                if(*(pattern+k)=='\0')
                {
                    fprintf(stdout, "find in file: %s lineno: %2d, %s", file, lineno, line);
                    break;
                }
            }
    }
    fclose(fp);
}