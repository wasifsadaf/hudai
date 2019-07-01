#include <stdio.h>
#define max_size 1500

char tempStore[705];

template <typename T>
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
    int size;

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
        size = 0;
    }

    int insertFirst(int root, T x)
    {
        size++;
        int newNode = createNode(x);
        list[newNode].next = root;
        return newNode;
    }

    int insertAny(int root, int pos, T x)
    {
        if (pos == 0)
            return insertFirst(root, x);
        int curr = root;
        for (int i = 1; i < pos; i++)
        {
            curr = list[curr].next;
        }
        if (list[curr].next == -1)
            return insertLast(root, x);

        int newNode = createNode(x);
        list[newNode].prev = curr;
        list[newNode].next = list[curr].next;
        list[list[curr].next].prev = newNode;
        list[curr].next = newNode;
        size++;
        return root;
    }

    int insertLast(int root, T x)
    {
        if (root == -1)
            return insertFirst(root, x);
        int curr = root;
        while (list[curr].next != -1)
        {
            curr = list[curr].next;
        }
        list[curr].next = createNode(x);
        list[list[curr].next].prev = curr;
        size++;
        return root;
    }

    int deleteFirst(int root)
    {
        size--;
        root = list[root].next;
        list[root].prev = -1;
        return root;
    }

    int deleteAny(int root, int pos)
    {

        if (pos == 0)
            return deleteFirst(root);
        size--;
        int curr = root;
        for (int i = 1; i < pos; i++)
        {
            curr = list[curr].next;
        }
        int newNextNode = list[list[curr].next].next;
        list[curr].next = newNextNode;
        if (newNextNode != -1)
        {
            list[newNextNode].prev = curr;
        }
        return root;
    }

    int deleteLast(int root)
    {

        if (list[root].next == -1)
        {
            return -1;
        }
        size--;
        int curr = root;
        while (list[list[curr].next].next != -1)
        {
            curr = list[curr].next;
        }
        list[curr].next = -1;
        return root;
    }

    int makeLast(int root, int pos)
    {

        int curr = root;
        for (int i = 1; i < pos; i++)
        {
            curr = list[curr].next;
        }
        if (curr == -1)
            return 0;
        int start = list[curr].next;
        list[curr].next = -1;
        int id = 0;
        while (start != -1)
        {
            tempStore[id++] = list[start].data;
            start = list[start].next;
        }
        size -= id;
        return id;
    }

    void printList(int root)
    {
        while (root != -1)
        {
            //cout << list[root].data << endl;
            printf("%c", list[root].data);
            root = list[root].next;
        }
        printf("\n");
    }
    void printReverse(int root)
    {
        while (list[root].next != -1)
            root = list[root].next;
        while (list[root].prev != -1)
        {
            //cout<< list[root].data << endl;
            printf("%c\n", list[root].data);
            root = list[root].prev;
        }
        //cout << list[root].data << endl;
        printf("%c\n", list[root].data);
    }
    void makeEmpty()
    {
        index = 0;
    }
    int getSize()
    {
        return size;
    }
    T getData(int root, int pos)
    {
        int cur = root;
        for(int i=1; i<pos; i++)
        {
            cur = list[cur].next;
        }
        return list[cur].data;
    }
};

DoublyLinkedList<char> dll[710];
int roots[710];
int link[710];
int index;
int msRoot;
int N;
int cRow;
int cCol;

int insertFirstRow(int root)
{
    int newRow = index++;
    link[newRow] = root;
    return newRow;
}

int insertAnyRow(int root, int pos)
{
    int curRow = root;
    for (int i = 1; i <= pos; i++)
    {
        curRow = link[curRow];
    }
    int newRow = index++;
    link[newRow] = link[curRow];
    link[curRow] = newRow;
    return root;
}

void init(int n)
{
    N = n;
    index = 0;
    msRoot = -1;
    for (int i = 0; i < 710; i++)
    {
        dll[i].makeEmpty();
        roots[i] = -1;
        link[i] = -1;
    }
    cRow = 0;
    cCol = 0;
    msRoot = insertFirstRow(msRoot);
}

void input_char(char in_char)
{
    int curRow = msRoot;
    for (int i = 1; i <= cRow; i++)
    {
        curRow = link[curRow];
    }
    roots[curRow] = dll[curRow].insertAny(roots[curRow], cCol, in_char);
    cCol++;
}

void input_newline()
{
    msRoot = insertAnyRow(msRoot, cRow);
    int curRow = msRoot;
    for (int i = 1; i <= cRow; i++)
    {
        curRow = link[curRow];
    }
    int count = dll[curRow].makeLast(roots[curRow], cCol);
    int nextRow = link[curRow];
    for (int i = count - 1; i >= 0; i--)
    {
        roots[nextRow] = dll[nextRow].insertFirst(roots[nextRow], tempStore[i]);
    }
    cRow++;
    cCol = 0;
}

void move_cursor(int direction)
{
    if (direction == 0)
    {
        if (cRow != 0)
        {
            cRow--;
            int curRow = msRoot;
            for (int i = 1; i <= cRow; i++)
            {
                curRow = link[curRow];
            }
            if (dll[curRow].getSize() - 1 < cCol)
            {
                cCol = dll[curRow].getSize();
            }
        }
    }
    else if(direction == 1)
    {
        if(cRow != index-1)
        {
            cRow++;
            int curRow = msRoot;
            for(int i=1;i<=cRow;i++)
            {
                curRow = link[curRow];
            }
            if(dll[curRow].getSize()-1 < cCol)
            {
                cCol = dll[curRow].getSize();
            }
        }
    }
    else if(direction == 2)
    {
        if(cCol != 0)
        {
            cCol--;
        }
        else if(cCol == 0 && cRow != 0)
        {
            cRow--;
            int curRow = msRoot;
            for(int i=1;i<=cRow;i++)
            {
                curRow = link[curRow];
            }
            cCol = dll[curRow].getSize();
        }
    }
    else
    {
        if(cCol < N-1)
        {
            cCol++;
        }
        else if(cCol == N-1 && cRow != N-1)
        {
            cRow++;
            cCol = 0;
        }
    }
    
}

char get_char(int row, int column)
{
    int curRow = msRoot;
    for(int i=1;i<row;i++)
    {
        curRow = link[curRow];
    }
    return dll[curRow].getData(roots[curRow],column);
}

int main()
{
    init(10);
    input_char('a');
    input_char('b');
    input_newline();
    input_newline();
    input_char('x');
    input_char('y');
    input_char('z');
    input_newline();
    input_char('.');
    input_newline();
    int travRoot = msRoot;
    while (travRoot != -1)
    {
        dll[travRoot].printList(roots[travRoot]);
        travRoot = link[travRoot];
    }
    printf("row: %d col: %d\n", cRow+1, cCol+1);
    int x = 100;
    for(int i=1;i<x;i++)
    {
        int a;
        scanf("%d",&a);
        move_cursor(a);
        printf("row: %d col: %d\n", cRow+1, cCol+1);
    }
    return 0;
}
