#include<iostream>
#include<stdexcept>

class Rational{
public:
    Rational(int x=0, int y=1);
    Rational & operator+(Rational &);
    Rational & operator-(Rational &);
    Rational & operator*(Rational &);
    Rational & operator/(Rational &);
    operator double() {return double (num)/(double)dnm;}
    int numerator() const{return num;}
    int denumerator() const{return dnm;}
    void print()const{std::cout<<num<<"/"<<dnm<<std::endl;}
private:
    int gcd(int x, int y);
    void approximate();
    int num;
    int dnm;
};

int Rational::gcd(int x, int y)
{
    int div;
    while(true)
    {
        div=x%y;
        if(div==0)
            return y;
        x=y;
        y=div;
    }
}

void Rational::approximate()
{
    int z=gcd(num, dnm);
    num/=z;
    dnm/=z;
}

Rational::Rational(int x, int y):num(x),dnm(y)
{
    if(y==0)
    {
        std::cout<<"error: bad denominator"<<std::endl;
        std::logic_error le("bad denominator");
        throw le;
    }
    approximate();
}

Rational & Rational::operator+(Rational &rhs)
{
    if(dnm==rhs.dnm)
    {
        num+=rhs.num;
        approximate();
        return *this;
    }
    num=num*rhs.dnm+rhs.num*dnm;
    dnm*=rhs.dnm;
    approximate();
    return *this;
}

Rational & Rational::operator-(Rational &rhs)
{
    if(dnm==rhs.dnm)
    {
        num-=rhs.num;
        return *this;
    }
    num=num*rhs.dnm-rhs.num*dnm;
    dnm*=rhs.dnm;
    approximate();
    return *this;
}

Rational & Rational::operator*(Rational &rhs)
{
    num*=rhs.num;
    dnm*=rhs.dnm;
    approximate();
    return *this;
}

Rational & Rational::operator/(Rational &rhs)
{
    if(rhs.num==0)
    {
        std::logic_error le("bad divisor");
        throw le;
        return *this;
    }
    num*=rhs.dnm;
    dnm*=rhs.num;
    approximate();
    return *this;
}



int main()
{
    Rational lhs(2,6), rhs(30, 60);
    lhs.print();
    rhs.print();
    Rational alhs=lhs+rhs;
    alhs.print();
    alhs=lhs-rhs;
    alhs.print();
    alhs=lhs*rhs;
    alhs.print();
    alhs=lhs/rhs;
    alhs.print();
    std::cout<<alhs<<std::endl;
    return 0;
}