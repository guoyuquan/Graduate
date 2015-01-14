#include<stdio.h>
#include<stdlib.h>

int pop();
void push(int n);

int main(int argc, char **argv)
{
    for(int i=0;i<argc;i++)
        printf("%s\n", argv[i]);
    int op2;
    while(--argc>0)
    {
        printf("%s %d\n",*argv, argc);
        switch(**++argv)
        {
            case '+' :
                push(pop()+pop());
                break;
            case '*' :
                push(pop()*pop());
                break;
            case '-' :
                op2=pop();
                push(pop()-op2);
                break;
            case '/' :
                op2=pop();
                if(op2==0)
                    printf("error: zero divisor\n");
                else
                    push(pop()/op2);
                break;
            default:
                if(**argv-'0'<=9&&**argv-'0'>=0)
                    push(atof(*argv));
                break;
        }
    }
    printf("%d \n", pop());
    return 0;
}

#define MAX 10

int stack[MAX];
int *bufp=stack;

int pop()
{
    if(bufp>stack)
        return *--bufp;
    else
    {
        printf("error: empty stack\n");
        exit(1);
    }
}

void push(int n)
{
    if(bufp-stack<=10)
        *bufp++=n;
    else
    {
        printf("error: stack is full\n");
    }
}