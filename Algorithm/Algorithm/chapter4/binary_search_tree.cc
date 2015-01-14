#include<iostream>

struct Node
{
    Node(int x=0, Node *l=0, Node *r=0):element(x), left(l), right(r){}
    int element;
    Node *left;
    Node *right;
};

class Binary
{
public:
    Binary():root(NULL){}
    Node *find(int x);
    Node *insert(int x);
    Node *delete_(int x);
    Node *find_min();
    Node *find_max();
    void print();
private:
    Node *root;
    Node *delete_tree(int x, Node *ptr);
    Node *find_min_1(Node *p);
    void real_print(Node *p);
};
Node * Binary::find(int x)
{
    Node *p=root;
    while(p!=NULL)
    {
        if(x<p->element)
            p=p->left;
        else if(x>p->element)
            p=p->right;
        else
            return p;
    }
    return p;
}

Node * Binary::insert(int x)
{
    if(root==NULL)
    {
        root=new Node(x);
    }
    Node *p=root, *temp;
    while(p!=NULL)
    {
        if(x<p->element)
        {
            temp=p;
            p=p->left;
        }
        else if(x>p->element)
        {
            temp=p;
            p=p->right;
        }
        else
            return p;
    }
    if(x<temp->element)
        temp->left=new Node(x);
    else
        temp->right=new Node(x);
    return p;
}

Node * Binary::find_min()
{
    return find_min_1(root);
}

Node * Binary::find_max()
{
    Node *p=root;
    if(p!=NULL)
        while(p->right!=NULL)
            p=p->right;
    return p;
}

Node * Binary::delete_(int x)
{
    return delete_tree(x, root);
}

Node *Binary::find_min_1(Node *p)
{
    if(p!=NULL)
        while(p->left!=NULL)
            p=p->left;
    return p;
}

Node * Binary::delete_tree(int x, Node *ptr)
{
    if(ptr==NULL)
    {
        return ptr;
    }
    Node *temp, *child;
    if(x<ptr->element)
        ptr->left=delete_tree(x, ptr->left);
    else if(x>ptr->element)
        ptr->right=delete_tree(x, ptr->right);
    else if(ptr->left&&ptr->right)
    {
        temp=find_min_1(ptr->right);
        ptr->element=temp->element;
        ptr->right=delete_tree(ptr->element, ptr->right);
    }
    else
    {
        std::cout<<long(temp)<<std::endl;
        temp=ptr;
        if(ptr->left==NULL)
            child=ptr->right;
        if(ptr->right==NULL)
            child=ptr->left;
        delete temp;
        return child;
    }
    return ptr;
}

void Binary::print()
{
    real_print(root);
}

void Binary::real_print(Node *r)
{
    if(r==NULL)
        return;
    if(r->left!=NULL)
        real_print(r->left);
    std::cout<<r->element<<std::endl;
    if(r->right!=NULL)
        real_print(r->right);
}

int main()
{
    int a[]={6,1,4,2,3,8,9,7,0,5};
    Binary tree;
    std::cout<<sizeof(tree)<<std::endl;
    for(int i=0; i<10; i++)
        tree.insert(*(a+i));
    tree.delete_(6);
    char * p=NULL;
    delete p;
    tree.print();
    return 0;
}