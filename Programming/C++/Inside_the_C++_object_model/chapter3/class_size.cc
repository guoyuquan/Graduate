#include<iostream>

class A{
};

class B: public virtual A{
};

class C: public virtual A{
};

class D: public B, public C{
};

class E: public C{
};

int main()
{
    std::cout<<"A: "<<sizeof (A)<<std::endl;
    std::cout<<"B: "<<sizeof (B)<<std::endl;
    std::cout<<"C: "<<sizeof (C)<<std::endl;
    std::cout<<"D: "<<sizeof (D)<<std::endl;
    std::cout<<"E: "<<sizeof (E)<<std::endl;
    return 0;
}