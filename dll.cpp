#include<stdio.h>
#define max_size 1500

template<typename T>
class DoublyLinkedList
{
private:
    struct Node
    {
        T data;
        int prev;
        int next;
    };

    Node list[max_size];
    int index;

    int createNode(T x)
    {
        int newNode;
        newNode = index++;
        list[newNode].data = x;
        list[newNode].prev = -1;
        list[newNode].next = -1;
        return newNode;
    }
public:
    DoublyLinkedList()
    {
        index = 0;
    }
    
    int insertFirst(int root, T x)
    {
        int newNode = createNode(x);
        list[newNode].next = root;
        return newNode;
    }

    int insertAny(int root, int pos, T x)
    {
        if(pos == 0) return insertFirst(root, x);
        int curr = root;
        for(int i=1;i<pos;i++)
        {
            curr = list[curr].next;
        }
        if(list[curr].next == -1) return insertLast(root, x);

        int newNode = createNode(x);
        list[newNode].prev = curr;
        list[newNode].next = list[curr].next;
        list[list[curr].next].prev = newNode;
        list[curr].next = newNode;

        return root;
    }

    int insertLast(int root, T x)
    {
        if(root == -1) 
            return insertFirst(root, x);
        int curr = root;
        while(list[curr].next != -1)
        {
            curr = list[curr].next;
        }
        list[curr].next = createNode(x);
        list[list[curr].next].prev = curr;
        return root;
    }

    int deleteFirst(int root)
    {
        root = list[root].next;
        list[root].prev = -1;
        return root;
    }

    int deleteAny(int root, int pos)
    {
        if(pos == 0)
            return deleteFirst(root);
        
        int curr = root;
        for(int i=1;i<pos;i++)
        {
            curr = list[curr].next;
        }
        int newNextNode = list[list[curr].next].next;
        list[curr].next = newNextNode;
        if(newNextNode != -1)
        {
            list[newNextNode].prev = curr;
        }
        return root;
    }

    int deleteLast(int root)
    {
        if(list[root].next == -1)
        {
            return -1;
        }
        int curr = root;
        while(list[list[curr].next].next != -1)
        {
            curr = list[curr].next;
        }
        list[curr].next = -1;
        return root;
    }

    void printList(int root)
    {
        while(root != -1)
        {
            //cout << list[root].data << endl;
            printf("%d\n",list[root].data);
            root = list[root].next;
        }
    }
    void printReverse(int root)
    {
        while(list[root].next != -1)
            root = list[root].next;
        while(list[root].prev != -1)
        {
            //cout<< list[root].data << endl;
            printf("%d\n",list[root].data);
            root = list[root].prev;
        }
        //cout << list[root].data << endl;
        printf("%d\n",list[root].data);
    }
    void makeEmpty()
    {
        index = 0;
    }
};

DoublyLinkedList<int> dll[710];
int roots[710];
int link[710];
int index;
int N;

void insertNewRow(int curId)
{
    int temp = link[curId];
    link[curId] = index;
    link[index] = temp;
    index++;
}

void init(int n)
{
    N = n;
    index = 0;
    for(int i=0;i<710;i++)
    {
        dll[i].makeEmpty();
        roots[i] = -1;
        link[i] = -1;
    }
}

int main()
{
    init(10);

    return 0;
}
