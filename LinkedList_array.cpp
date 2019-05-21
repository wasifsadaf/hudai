#include <stdio.h>

#define SIZE 501

typedef struct nodeStruct {
    int data;
    int next;
} NODE;

NODE nodes[SIZE];
int index;

int createNode(int n)
{
    int newNode;
    newNode = index++;
    nodes[newNode].data = n;
    nodes[newNode].next = -1;

    return newNode;
}

void deleteNode(int nodeToDelete)
{
    nodes[nodeToDelete].data = -1;
    nodes[nodeToDelete].next = -1;
}

int insertFirst(int root, int data)
{
    int newNode = createNode(data);
    nodes[newNode].next = root;

    return newNode;
}

int insertAnyPosition(int root, int pos, int data)
{
    if (pos == 0)
    {
        return insertFirst(root, data);
    }
    int curr = root;
    for (size_t i = 1; i < pos; i++)
    {
        curr = nodes[curr].next;
    }

    int newNode = createNode(data);
    nodes[newNode].next = nodes[curr].next;
    nodes[curr].next = newNode;

    return root;
}

int insertLast(int root, int data)
{
    int curr = root;
    while (nodes[curr].next != -1)
    {
        curr = nodes[curr].next;
    }
    nodes[curr].next = createNode(data);

    return root;
}

int deleteFirst(int root)
{
    int oldRoot = root;
    root = nodes[root].next;
    deleteNode(oldRoot);

    return root;
}

int deleteAnyPosition(int root, int pos)
{
    if (pos == 0)
    {
        return deleteFirst(root);
    }
    int curr = root;
    for (size_t i = 1; i < pos; i++)
    {
        curr = nodes[curr].next;
    }

    int nodeToDelete = nodes[curr].next;
    nodes[curr].next = nodes[nodeToDelete].next;

    deleteNode(nodeToDelete);

    return root;
}

int deleteLast(int root)
{
    if (nodes[root].next == -1)
    {
        deleteNode(root);
        root = -1;

        return root;
    }
    int curr = root;
    while(nodes[nodes[curr].next].next != -1)
    {
        curr = nodes[curr].next;
    }
    deleteNode(nodes[curr].next);
    nodes[curr].next = -1;
    return root;
}

void printList(int root)
{
    while (root != -1)
    {
        printf("%d ", nodes[root].data);
        root = nodes[root].next;
    }
    printf("\n");
}

int main()
{
    int root = -1;
    root = createNode(1);
    root = insertFirst(root,0);
    root = insertLast(root,3);
    root = insertAnyPosition(root,2,2);
    root = insertAnyPosition(root,4,4);
    root = insertLast(root,5);
    printList(root);
    for(int i=5; i>=0; i--)
    {
        root = deleteAnyPosition(root,i);
        printList(root);
    }
    return 0;
}

