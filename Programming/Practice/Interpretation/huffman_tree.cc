#include<iostream>

struct Node{
    Node(int w=0, Node *l=NULL, Node *r=NULL):weight(w), left(l), right(r){}
    char weight;
    Node *left;
    Node *right;
};

struct Alphabet{
    char alpha;
    int frequency;
};

void shellsort(Alphabet *a, int n)
{
    static int inc[]={1, 3, 7, 11, 13};
    for(int i=4; i>=0; i--)
    {
        for(int j=inc[i]-1; j<n; j++)
        {
            Alphabet temp=a[j];
            int k=j;
            for(; k>=inc[i]; k-=inc[i])
                if(temp.frequency<a[k-inc[i]].frequency)
                    a[k]=a[k-1];
                else break;
            a[j]=temp;
        }
        
    }
}

class Huffman{
public:
    Huffman(Alphabet *, int);
    void encoding(std::string &s);
    void decoding(std::string &s);
private:
    void construct();
    Node *root;
};
void construct(Alphabet *a, int n)
{
    shellsort(a, n);
    
}

int main()
{
}