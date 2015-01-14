#include<iostream>
#include<stdexcept>

template<typename T>
struct Node{
    Node(T ele=0, int n=0):element(ele),left(NULL), right(NULL), npl(n){}
    T element;
    Node *left;
    Node *right;
    int npl;
};

template<typename T>
class Leftist{
public:
    Leftist(Node<T> *p=NULL):root(p){}
    Leftist merge(Leftist l1, Leftist l2);
    void insert(T x);
    T delete_min();
private:
    Leftist real_merge(Node<T> *, Node<T> *);
    void swap_children(Node<T> *p){
        Node<T> *temp=p->right;
        p->right=p->left;
        p->left=temp;
    }
    Node<T> * root;
};

template <typename T>
T Leftist<T>::delete_min()
{
    if(root==NULL)
    {
        std::cout<<"no element"<<std::endl;
        return -1;
    }
    T temp=root->element;
    Node<T> * ret=merge(Leftist<T>(root->left),Leftist<T>(root->right)).root;
    delete root;
    root=ret;
    return temp;
}

template <typename T>
void Leftist<T>::insert(T x)
{
    Node<T> *temp=new Node<T>(x);
    if(temp==NULL)
    {
        std::bad_alloc ba;
        std::cout<<"out of space"<<std::endl;
        throw ba;
    }
    root=merge(Leftist<T>(temp), Leftist<T>(root)).root;
}

template <typename T>
Leftist<T>  Leftist<T>::real_merge(Node<T> *n1, Node<T> *n2)
{
    if(n1->left==NULL)
        n1->left=n2;
    else
    {
        n1->right=merge(Leftist<T>(n1->right), Leftist<T>(n2)).root;
        if(n1->left->npl<n1->right->npl)
            swap_children(n1);
        n1->npl=n1->right->npl+1;
    }
    return n1;
}

template <typename T>
Leftist<T> Leftist<T>::merge(Leftist<T> l1, Leftist<T> l2)
{
    if(l1.root==NULL)
        return l2;
    if(l2.root==NULL)
        return l1;
    if(l1.root->element <l2.root->element)
        return real_merge(l1.root, l2.root);
    return real_merge(l2.root, l1.root);
}

int main()
{
    Leftist<int> left;
    for(int i=10;i>0;i--)
        left.insert(i);
    for(int i=0;i<10;i++)
        std::cout<<left.delete_min()<<" ";
    std::cout<<std::endl;
    return 0;
    
}
