#include<iostream>

template <typename T>
struct Node 
{
    Node(T ele=0, int hei=0, Node *le=NULL, Node *ri=NULL):element(ele), left(le), right(ri), height(hei){}
    T element;
    Node *left;
    Node *right;
    int height;
};

template <typename T>
class Binary
{
public:
    Binary():root(NULL){}
    void insert(T x);
    Node<T> * find(T x);
    void Delete(T x);
    void print();
private:
    Node<T> * root;
    int height(Node<T> *p){
        if(p!=NULL)
            return p->height;
        return -1;
    }
    Node<T> * singleLeftRotate(Node<T> * p);
    Node<T> * singleRightRotate(Node<T> * p);
    Node<T> * doubleLRRotate(Node<T> * p);
    Node<T> * doubleRLRotate(Node<T> * p);
    Node<T> * real_insert(Node<T> *, T x);
    Node<T> * real_delete(Node<T> *, T);
    Node<T> * delete_tree(Node<T> *, T);
    Node<T> * find_min(Node<T> *);
    void real_print(Node<T> *);
};

template <typename T>
void Binary<T>::insert(T x)
{
    real_insert(root, x);
}

template <typename T>
void Binary<T>::Delete(T x)
{
    real_delete(root, x);
}

template <typename T>
Node<T> * Binary<T>::singleLeftRotate(Node<T> * p)//left left
{
    Node<T> * temp=p->left;
    p->left=temp->right;
    temp->right=p;
    
    p->height=std::max(height(p->left), height(p->right))+1;
    temp->height=std::max(height(temp->left), height(temp->right))+1;
    return temp;
}

template <typename T>
Node<T> * Binary<T>::singleRightRotate(Node<T> * p)//right right
{
    Node<T> * temp=p->right;
    p->right=temp->left;
    temp->left=p;
    
    p->height=std::max(height(p->right), height(p->left))+1;
    temp->height=std::max(height(temp->right), height(temp->right))+1;
    return temp;
}

template <typename T>
Node<T> * Binary<T>::doubleLRRotate(Node<T> *p) //left right
{
    p->right=singleLeftRotate(p->right);
    return singleRightRotate(p);
}

template <typename T>
Node<T> *Binary<T>::doubleRLRotate(Node<T> *p) //right left
{
    p->left=singleRightRotate(p->left);
    return singleLeftRotate(p);
}

template <typename T>
Node<T> *Binary<T>::real_insert(Node<T> * p, T x)
{
    if(p==NULL)
    {
        p=new Node<T>(x);
        root=p;
        return p;
    }
    if(x<p->element)
    {
        real_insert(p->left, x);
        if(height(p->left)-height(p->right)==2)
        {
            if(x<p->left->element)
                p=singleLeftRotate(p);
            else
                p=doubleLRRotate(p);
        }
    }
    else if(x>p->element)
    {
        real_insert(p->right, x);
        if(height(p->right)-height(p->left)==2)
        {
            if(x>p->right->element)
                p=singleRightRotate(p);
            else
                p=doubleRLRotate(p);
        }
    }
    else
    {
        return p;
    }
    p->height=std::max(height(p->left), height(p->left));
    return p;
}

template <typename T>
Node<T> * Binary<T>::find(T x)
{
    Node<T> *p=root;
    while(p!=NULL&&p->element!=x)
        if(x>p->element)
            p=p->right;
        else
            p=p->left;
    return p;
}

template <typename T>
Node<T> * Binary<T>::real_delete(Node<T> *p, T x)
{
    if(p==NULL)
        return p;
    if(x<p->element)
    {
        real_delete(p->left, x);
        if(height(p->right)-height(p->left)==2)
        {
            if(p->right->left!=NULL&&height(p->right->left)>height(p->right->left))
                p=doubleRLRotate(p);
            else
                p=singleRightRotate(p);
        }
    }
    else if(x>p->element)
    {
        real_delete(p->right, x);
        if(height(p->left)-height(p->right)==2)
        {
            if(p->left->right!=NULL&&height(p->left->right)>height(p->left->left))
                p=doubleLRRotate(p);
            else
                p=singleLeftRotate(p);
        }
    }
    else
    {
        delete_tree(p, x);
    }
    p->height=std::max(height(p->left), height(p->right));
    return p;
}

template <typename T>
Node<T> * Binary<T>::delete_tree(Node<T> *ptr, T x)
{
    if(ptr==NULL)
    {
        return ptr;
    }
    Node<T> *temp, *child;
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

template <typename T>
Node<T> *Binary<T>::find_min(Node<T> * p)
{
    if(p!=NULL)
        while(p->left!=NULL)
            p=p->left;
    return p;
}

template <typename T>
void Binary<T>::print()
{
    real_print(root);
}

template <typename T>
void Binary<T>::real_print(Node<T> * p)
{
    if(p==NULL)
        return;
    if(p->left!=NULL)
        real_print(p->left);
    std::cout<<p->element<<std::endl;
    if(p->right!=NULL)
        real_print(p->right);
}



