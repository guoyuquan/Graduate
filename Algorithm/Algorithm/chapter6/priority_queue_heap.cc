#include<iostream>

template <typename T>
class Priority{
public:
    Priority(int max=10):sz(0), max_size(max), arr(new T[max]){}
    Priority(T *a, int n);
    Priority(Priority &);
    Priority & operator=(Priority);
    void swap(Priority &);
    void insert(T x);
    int size(){return size;}
    T delete_min();
    void print();
    ~Priority(){delete []arr;}
private:
    void build_heap();
    void sift_down(int index);
    int sz;
    int max_size;
    T * arr;
};

template <typename T>
void Priority<T>::print()
{
    for(int i=0; i<sz; i++)
        std::cout<<*(arr+i)<<" ";
    std::cout<<std::endl;
}

template <typename T>
void Priority<T>::swap(Priority & p)
{
    using std::swap;
    swap(sz, p.sz);
    swap(max_size, p.max_size);
    swap(arr, p.arr);
}

template <typename T>
Priority<T>::Priority(T *a, int n):sz(n), max_size(n),arr(new T[n])
{
    for(int i=0; i<n; i++)
        *(arr+i)=*(a+i);
    build_heap();
}

template <typename T>
void Priority<T>::sift_down(int index)
{
    while(index*2<=sz)
    {
        if(index*2==sz)
        {
            if(arr[index-1]<=arr[sz-1])
                return;
            std::swap(arr[index-1], arr[sz-1]);
            return;
        }
        if(arr[index*2]>arr[index*2-1])
        {
            if(arr[index-1]>arr[index*2-1])
            {
                std::swap(arr[index-1],arr[index*2-1]);
                index*=2;
                continue;
            }
            break;
        }
        else 
        {
            if(arr[index*2]<arr[index-1])
            {
                std::swap(arr[index-1],arr[index*2]);
                index=index*2+1;
                continue;
            }
            break;
        }
    }
}

template <typename T>
void Priority<T>::build_heap()
{
    for(int i=sz/2; i>0;i--)
        sift_down(i);
        
}

template <typename T>
Priority<T>::Priority(Priority & p)
{
    if(arr==p.arr)
        return;
    arr=new T[p.sz];
    for(int i=0; i<p.sz; i++)
        *(arr+i)=*(p.arr+i);
    sz=p.sz;
    max_size=p.max_size;
}

template <typename T>
Priority<T> & Priority<T>::operator=(Priority p)
{
    swap(p);
    return *this;
}

template <typename T>
void Priority<T>::insert(T x)
{
    if(sz>=max_size)
    {
        std::cout<<"error: queue is full"<<std::endl;
        return;
    }
    if(sz==0)
    {
        *arr=x;
        sz++;
        return;
    }
    int i=sz++;
    while(i!=0&&*(arr+i/2)>x)
    {
        *(arr+i)=*(arr+i/2);
        i/=2;
    }
    *(arr+i)=x;
}

template <typename T>
T Priority<T>::delete_min()
{
    if(sz==0)
    {
        std::cout<<"empty queue"<<std::endl;
        return -1;
    }
    int index=1, i=--sz;
    int temp=*(arr+sz), ret=*arr;
    while(index<=(sz+1)/2)
    {
        if(index*2==sz+1)
        {
            *(arr+index-1)=*(arr+sz);
               return ret;
        }
        if(*(arr+2*index-1)<*(arr+2*index))
        {
            if(temp<*(arr+2*index-1))
            {
                *(arr+index-1)=temp;
                return ret;
            }
            *(arr+index-1)=*(arr+2*index-1);
            index=2*index;
        }
        else
        {
            if(temp<*(arr+2*index))
            {
                *(arr+index-1)=temp;
                return ret;
            }
            *(arr+index-1)=*(arr+2*index);
            index=2*index+1;
        }
    }
    *(arr+index-1)=temp;
    return ret;
}

int main()
{
    int a[]={0,9,8,7,6,5,4,3,2,1};
    Priority<int> p(a,10);
    for(int i=0; i<12; i++)
    {
        //p.delete_min();
        std::cout<<p.delete_min()<<" ";
        //p.print();
    }
    std::cout<<std::endl;
    
    return 0;
}