#include<iostream>
#include<queue>
#include<stdexcept>

template<typename T>
struct Node{
    Node(int ele=0, int w=0, Node *n=NULL):element(ele), weight(w), next(n){}
    T element;
    int weight;
    Node *next;
};

template <typename T>
class List{
public:
    List(Node<T> * n=NULL):head(n){}
    void insert(T x, int w);
    void delete_node(T x);
    Node<T> * find(T x);
    T get_pos(int n);
    T get_min_weight();
    void print();
    ~List();
private:
    Node<T> *head;
};

template<typename T>
T List<T>::get_min_weight()
{
    Node<T> *p=head;
    int temp=666666, no=-1;
    while(p!=NULL)
    {
        if(p->weight<temp)
        {
            temp=p->weight;
            no=p->element;
        }
        p=p->next;
    }
    return no;
}

template<typename T>
T List<T>::get_pos(int n)
{
    Node<T> *p=head;
    for(int i=0; p!=NULL&&i<n; i++)
    {
        p=p->next;
    }
    if(p!=NULL)
        return p->element;
    return -1;
}
template<typename T>
void List<T>::insert(T x, int w)
{
    if(head==NULL)
    {
        head=new Node<T>(x, w);
        if(head==NULL)
        {
            std::bad_alloc ba;
            throw ba;
        }
        return;
    }
    Node<T> * p=head;
    while(p->next!=NULL)
        p=p->next;
    p->next=new Node<T>(x,w);
    if(p->next==NULL)
    {
        std::bad_alloc ba;
        throw ba;
    }
}

template<typename T>
void List<T>::delete_node(T x)
{
    if(head==NULL)
        return;
    if(head->element==x)
        return;
    Node<T> *p=head;
    while(p->next!=NULL&&p->next->element!=x)
        p=p->next;
    if(p->next!=NULL)
    {
        Node<T> temp=p->next;
        p->next=temp->next;
        delete temp;
    }
}

template<typename T>
Node<T> * List<T>::find(T x)
{
    Node<T> *p=head;
    while(p!=NULL&&p->element!=x)
        p=p->next;
    return p;
}

template<typename T>
List<T>::~List()
{
    while(head!=NULL)
    {
        Node<T> *p=head;
        head=head->next;
        delete p;
    }
}

template<typename T>
void List<T>::print()
{
    Node<T> *p=head;
    while(p!=NULL)
    {
        std::cout<<p->element<<" weight: "<<p->weight<<", ";
        p=p->next;
    }
    std::cout<<std::endl;
}

struct table{
    table(int v=0, int d=0, int pa=0, bool f= false):vertex(v), known(f), dis(d), path(pa){}
    int vertex;
    bool known;
    int dis;
    int path;
};

template<typename T>
class Graph{
public:
    void short_path(T ver);
    Graph(int n, table * p=NULL):sz(n),list(new List<T>[n]), shortpath(new table[n]){}
    void insert(int node, T *ver, int*, int n);
    int indegree(int node);
    void print();
    int size(){return sz;}
    void shortest_path(T, T);
    ~Graph();
private:
    bool all();
    int sz;
    List<T> * list;
    table *shortpath;
};
template<typename T>
bool Graph<T>::all()
{
    for(int i=0; i<sz; i++)
    {
        if(shortpath[i].known==false)
        {
            return false;
        }
    }
    return true;
}

template<typename T>
void Graph<T>::insert(int node, T *ver, int * w, int n)
{
    for(int i=0; i<n; i++)
        list[node-1].insert(ver[i], w[i]);
}

template<typename T>
int Graph<T>::indegree(int node)
{
    int j, num=0;
    for(int i=0; i<sz; i++)
        if(list[i].find(node)!=NULL)
            num++;
    return num;
}

template<typename T>
void Graph<T>::print()
{
    for(int i=0; i<sz; i++)
    {
        std::cout<<"vertex "<<i+1<<": ";
        list[i].print();
    }
}

template<typename T>
void Graph<T>::shortest_path(T start, T end)
{
    int cnt=0;
    for(int i=start; cnt<sz; cnt++)
    {
        std::cout<<i<<" -> ";
        i=list[i-1].get_min_weight();
        if(i==-1)
        {
            std::cout<<end<<" have no path"<<std::endl;
            return;
        }
        if(i==end)
        {
            std::cout<<i;
            break;
        }
    }
    std::cout<<std::endl;
}

template<typename T>
Graph<T>::~Graph()
{
    delete []list;
    if(shortpath!=NULL)
        delete []shortpath;
}


template<typename T>
void Graph<T>::short_path(T v)
{
    std::queue<int> q;
    for(int i=0; i<sz; i++)
    {
        shortpath[i].vertex=i+1;
    }
    shortpath[v-1].path=v;
    shortpath[v-1].dis=1;
    shortpath[v-1].known=false;
    q.push(v);
    while(!q.empty()&&!all())
    {
        T temp=q.front();
        q.pop();
        for(int i=0, ver=0; (ver=list[temp-1].get_pos(i))!=-1; i++)
        {
            q.push(ver);
            Node<T> *node=list[temp-1].find(ver);
            if(shortpath[ver-1].known==false)
            {
                shortpath[ver-1].known=true;
                shortpath[ver-1].dis=shortpath[temp-1].dis+node->weight;
                shortpath[ver-1].path=temp;
            }
            else
            {
                if(shortpath[temp-1].dis+node->weight<shortpath[ver-1].dis)
                {
                    shortpath[ver-1].dis=shortpath[temp-1].dis+node->weight;
                    shortpath[ver-1].path=temp;
                }
            }
        }
    }
    for(int i=1; i<sz; i++)
    {
        std::cout<<"node "<<shortpath[0].vertex<<" to node"<<shortpath[i].vertex<<" distance is :"<<shortpath[i].dis<<" through"<<shortpath[i].path<<std::endl;
    }
}

int main()
{
    Graph<int> graph(7);
    int a[]={2,4};
    int w1[]={2, 1};
    graph.insert(1, a, w1, 2);
    int b[]={4,5};
    int w2[]={3,10};
    graph.insert(2, b, w2, 2);
    int c[]={1,6};
    int w3[]={4, 5};
    graph.insert(3, c, w3, 2);
    int d[]={3,6,7};
    int w4[]={2, 8,5};
    graph.insert(4, d, w4, 2);
    int e[]={7};
    int w5[]={6};
    graph.insert(5, e, w5, 1);
    int f[]={6};
    int w6[]={1};
    graph.insert(7, f, w6, 1);
    graph.print();
    for(int i=0; i<graph.size(); i++)
    {
        std::cout<<"indegree of vertex "<<i+1<<"is: "<<graph.indegree(i+1)<<std::endl;
    }
    graph.shortest_path(1, 6);
    graph.short_path(1);
    return 0;
}



