#include<iostream>
#include<stdexcept>

template<typename T>
struct Node{
    Node():element(0), next(NULL){}
    T element;
    Node *next;
};

template <typename T>
class List
{
public:
    List():header(new Node<T>){}
    ~List();
    bool is_empty(){return header->next==NULL;}
    bool is_last(Node<T> *p){return p->next==NULL;}
    Node<T> *find(T x);
    Node<T> *find_previous(T x);
    void delete_(T x);
    void insert(T x, Node<T> *p);
    void print();
private:
    Node<T> *header;
    List(List &);
    List & operator=(List &);
};

template <typename T>
List<T>::~List()
{
    Node<T> *p=header->next, *dp;
    delete header;
    header=NULL;
    header->next=NULL;
    while(p!=NULL)
    {
        dp=p;
        p=p->next;
        delete dp;
    }
}

template <typename T>
Node<T> * List<T>::find(T x)
{
    Node<T> *p=header->next;
    while(p!=NULL&&p->element!=x)
        p=p->next;
    return p;
    
}

template <typename T>
Node<T> *List<T>::find_previous(T x)
{
    Node<T> *p=header;
    while(p->next!=NULL&&p->next->element==x)
        p=p->next;
    return p->next==NULL?NULL:p;
}

template <typename T>
void List<T>::delete_(T x)
{
    Node<T> *p=find_previous(x);
    if(p==NULL)
        return;
    Node<T> *dp=p->next;
    p->next=dp->next;
    delete dp;
}

template <typename T>
void List<T>::insert(T x, Node<T> *p)
{
    Node<T> *temp;
    try
    {
        temp=new Node<T>;
    }
    catch(std::bad_alloc ba)
    {
        std::cout<<ba.what()<<std::endl;
        exit(1);
    }
    temp->element=x;
    temp->next=p->next;
    p->next=temp;
}

template <typename T>
void List<T>::print()
{
    Node<T> *p=header->next;
    while(p!=NULL)
    {
        std::cout<<p->element<<" ";
        p=p->next;
    }
    std::cout<<std::endl;
}

int main()
{
    std::cout<<sizeof (List<long>)<<std::endl;
    List<int> ilist;
    for(int i=0; i<10; i++)
    {
    }
    return 0;
}