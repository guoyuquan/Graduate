#include <iostream>
template <typename T>
struct Node{
    Node(T ele=0, Node * n=NULL):element(ele), next(n){}
    T element;
    Node *next;
};

template <typename T>
class List{
public:
    List():head(NULL){}
    Node<T> * find(T x);
    const Node<T> * insert(T x);
    void delete_(T x);
    void print();
    ~List();
private:
    Node<T> * head;
};

template <typename T>
Node<T> * List<T>::find(T x)
{
    Node<T> *p=head;
    while(p!=NULL&&p->element!=x)
        p=p->next;
    return p;
}

#include <stdexcept>
template <typename T>
const Node<T> * List<T>::insert(T x)
{
    if(head==NULL)
    {
        try
        {
            head=new Node<T>(x);
        }catch(std::bad_alloc ba)
        {
            std::cout<<ba.what()<<std::endl;
            exit(1);
        }
    }
    else
    {
        Node<T> *temp=find(x);
        if(temp==NULL)
        {
            try
            {
                temp=new Node<T>(x);
            }catch(std::bad_alloc ba)
            {
                std::cout<<ba.what()<<std::endl;
            }
            temp->next=head;
            head=temp;
        }
        else
            return temp;
    }
    return head;
}

template <typename T>
void List<T>::delete_(T x)
{
    if(head==NULL)
        return;
    Node<T> * temp=head, * pre=head;
    while(temp!=NULL&&temp->element!=x)
    {
        pre=temp;
        temp=temp->next;
    }
    if(temp==NULL)
        return;
    if(temp==head)
    {
        delete head;
        head=NULL;
    }
    pre->next=temp->next;
    delete temp;
    temp=NULL;
}

template <typename T>
void List<T>::print()
{
    Node<T> * p=head;
    while(p!=NULL)
    {
        std::cout<<p->element<<" ";
        p=p->next;
    }
}

template <typename T>
List<T>::~List()
{
    Node<T> *p=head;
    while(p!=NULL)
    {
        delete p;
        p=p->next;
    }
}

template <typename T>
class Hash{
public:
    Hash(int k=10):hptr(new List<T> [k]), H_Size(k){}
    const int size(){return H_Size;}
    Node<T> * find(T x);
    const Node<T> * insert(T x);
    void delete_(T x);
    void print();
    ~Hash(){delete []hptr;}
private:
    int hash(T x){return x%H_Size;}
    List<T> * hptr;
    const int H_Size;
};

template <typename T>
const Node<T> * Hash<T>::insert(T x)
{
    return (*(hptr+hash(x))).insert(x);
}

template <typename T>
Node<T> * Hash<T>::find(T x)
{
    return (*(hptr+hash(x))).find(x);
}

template <typename T>
void Hash<T>::delete_(T x)
{
    (*(hptr+hash(x))).delete_(x);
}

template <typename T>
void Hash<T>::print()
{
    for(int i=0; i<H_Size; i++)
    {
        (*(hptr+i)).print();
        std::cout<<std::endl;
    }
}

int main()
{
    Hash<int> hash;
    for(int i=0; i<100; i++)
        hash.insert(i);
    hash.print();
    for(int i=1; i<100; i+=11)
        hash.delete_(i);
    hash.print();
    return 0;
}


