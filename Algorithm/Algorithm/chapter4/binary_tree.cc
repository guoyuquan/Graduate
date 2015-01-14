#include<iostream>
struct Node
{
    Node():left(NULL), right(NULL){}
    std::string element;
    Node *left;
    Node *right;
};


class Stack
{
public:
    Stack(){}
    Node * pop();
    void push(Node * val){
        if(top>9)
        {
            std::cout<<"stack overflow"<<std::endl;
            exit(2);
        }
        a[top++]=val;
    }
    static bool is_empty(){return top==0?true:false;}
    ~Stack(){};
private:
    Stack(Stack &);
    Stack & operator=(Stack &);
    Node * a[10];
    static int top;
};

int Stack::top=0;

Node * Stack::pop()
{
    if(is_empty())
    {
        std::cout<<"stack underflow"<<std::endl;
        exit(1);
    }
    return a[--top];
    
}

void print(Node *p)
{
    if(p->left!=NULL)
        print(p->left);
    if(p!=NULL)
        std::cout<<p->element;
    if(p->right!=NULL)
        print(p->right);
}



int main()
{
    //Node<int> node;
    Stack stack;
    std::string ival;
    while(std::cin>>ival)
    {
        //std::cout<<ival<<std::endl;
        switch(ival[0])
        {
            case '+' :
            case '*' :
            case '/' :
            case '-' :
            {
                Node *p1=new Node;
                p1->element=ival;
                p1->right=stack.pop();
                p1->left=stack.pop();
                stack.push(p1);
                break;
            }
            case ' ' :
                break;
            default:
            {
                Node *p=new Node;
                p->element=ival;
                stack.push(p);
                break;
            }
        }
    }
    print(stack.pop());
    std::cout<<std::endl;
}