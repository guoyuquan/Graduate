#include<iostream>
#include<stdexcept>
using std::string;

struct Node{
    Node(int c=0, string s="", Node *n=NULL):coefficient(c), term(s), next(n){}
    int coefficient;
    string term;
    Node *next;
};

class List{
public:
    List(Node *r=NULL):root(r){}
    void insert(int, string);
    string formular();
    ~List();
private:
    string itoa(int);
    Node *root;
};

string List::itoa(int n)
{
    if(n<0)
        n=-n;
    string ret;
    do{
        ret.push_back(n%10);
    }while((n=n/10)>0);
    for(int i=0, j=ret.size()-1; i<j; i++, j--)
    {
        char ch=ret[i];
        ret[i]=ret[j];
        ret[j]=ch;
    }
    return ret;
}

void List::insert(int c, string term)
{
    if(root==NULL)
    {
        root=new Node(c, term);
        if(root==NULL)
        {
            std::bad_alloc ba;
            throw ba;
        }
        return;
    }
    Node *pt=root;
    while(pt->next!=NULL)
        pt=pt->next;
    pt->next=new Node(c, term);
    if(pt->next==NULL)
    {
        std::bad_alloc ba;
        throw ba;
    }
}

string List::formular()
{
    if(root==NULL)
    {
        return "";
    }
    string ret;
    ret+=itoa(root->coefficient);
    ret+="*";
    ret+=root->term;
    Node *p=root->next;
    while(p!=NULL)
    {
        if(p->coefficient<0)
            ret.push_back('-');
        else
            ret.push_back('+');
        ret+=itoa(p->coefficient);
        ret+="*";
        ret+=p->term;
        p=p->next;
    }
    return ret;
}

List::~List()
{
    while(root!=NULL)
    {
        delete root;
        root=root->next;
    }
}

class Algebra{
public:
    Algebra(string s="");
    Algebra & operator*(Algebra & rhs);
    Algebra & operator+(Algebra & rhs);
    void print(){std::cout<<equation.formular()<<std::endl;}
private:
    void construct(string s);
    int stoi(string s);
    List equation;
};

int Algebra::stoi(string s)
{
    int ret=0;
    for(int i=0; i<s.size(); i++)
        ret=ret*10+s[i]-'0';
    return ret;
}

Algebra::Algebra(string s)
{
    construct(s);
}

void Algebra::construct(string s)
{
    for(int i=0; i<s.size(); i++)
    {
        int coe;
        string term;
        if(s[i]=='+')
        {
            int j;
            for(i+=1,j=0; i+j<s.size()&&(s[i+j]>='0'&&s[i+j]<='9');)
                j++;
            coe=stoi(s.substr(i, j));
            i+=j;
        }
         else if(s[i]=='-')
            {
                int j;
                for(i+=1, j=0; i+j<s.size()&&(s[i+j]>='0'&&s[i+j]<='9');)
                    j++;
                coe=-stoi(s.substr(i, j));
                i+=j;
            }
        if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))
        {
            int j;
            for(j=0; i+j<s.size()&&((s[i+j]>='a'&&s[i+j]<='z')||(s[i+j]>='A'&&s[i+j]<='Z'));j++)
                ;
            term=s.substr(i, j);
            i+=j-1;
        }
        equation.insert(coe, term);
    }
}

int main()
{
    Algebra a("2a+3b");
    a.print();
    return 0;
}


