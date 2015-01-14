#include<iostream>
#include<stdio.h>

class A{
public:
    A():a(10),b(20), c(30){}
    virtual void f(){};
    int * ap(){return &a;}
    int * bp(){return &b;}
    int * cp(){return &c;}
    //int *pp(){return p;}
    static int A::*repa(){return &A::a;}
    static int A::*repb(){return &A::b;}
    static int A::*repc(){return &A::c;}
    static char A::*ww(){return &A::ch;}
private:
    char ch;
    int a;
    int b;
    int c;
};

int A::*pa=A::repa();
int A::*pb=A::repb();
int A::*pc=A::repc();
char A::*pch=A::ww();
int main()
{
    A a;
    A *p=&a;
    int *ap=p->ap();
    int *bp=p->bp();
    std::cout<<"size: "<<sizeof (A)<<std::endl;
    std::cout<<"start: "<<p<<std::endl;
    std::cout<<"int a: "<<ap<<std::endl;
    std::cout<<"int b: "<<bp<<std::endl;
    std::cout<<"int c: "<<a.cp()<<std::endl;
    std::cout<<"int a:"<<p->*pa<<std::endl;
    std::cout<<"int pa "<<*(int *)&pa<<std::endl;
    std::cout<<"int b:"<<p->*pb<<std::endl;
    std::cout<<"int pb "<<*(long *)&pb<<std::endl;
    std::cout<<"int c:"<<p->*pc<<std::endl;
    std::cout<<"int pc "<<*(long *)(&pc)<<std::endl;
    std::cout<<"pa size: "<<sizeof (pa)<<std::endl;
    fprintf(stdout,"%d\n", pa);
    std::cout<<pch<<std::endl;
    pa==pb?std::cout<<"equal":std::cout<<"not"<<pa<<" "<<pb;

    return 0;
}