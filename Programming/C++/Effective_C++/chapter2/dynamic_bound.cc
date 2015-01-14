class A
{
};

class B:public A
{
};

int main()
{
    A a, *ap;
    B b, *bp;
    ap=&b; //base to derive: OK
    bp=&a; //derive to base: error
}