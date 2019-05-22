#include<stdio.h>
#include<stdlib.h>

typedef struct nodeStruct
{
    int data;
    struct nodeStruct *next;
}NODE;

NODE *createNode(int n)
{
    NODE *newNode = NULL;
    newNode = (NODE *) malloc(sizeof(NODE));
    newNode->data = n;
    newNode->next = NULL;
    return newNode;
}

void deleteNode(NODE* nodeToDelete)
{
    free(nodeToDelete);
}

NODE *insertFirst(NODE *root, int data)
{
    NODE *newNode = createNode(data);
    newNode->next = root;

    return newNode;
}

NODE *insertAnyPosition(NODE *root, int pos, int data)
{
    if (pos == 0)
    {
        return insertFirst(root, data);
    }
    NODE* curr = root;
    for (size_t i = 1; i < pos; i++)
    {
        curr = curr->next;
    }

    NODE* newNode = createNode(data);
    newNode->next = curr->next;
    curr->next = newNode;

    return root;
}

NODE *insertLast(NODE *root, int data)
{
    NODE *curr = root;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = createNode(data);

    return root;
}

NODE *deleteFirst(NODE *root)
{
    NODE *oldRoot = root;
    root = root->next;
    deleteNode(oldRoot);

    return root;
}

NODE *deleteAnyPosition(NODE *root, int pos)
{
    if (pos == 0)
    {
        return deleteFirst(root);
    }
    NODE *curr = root;
    for (size_t i = 1; i < pos; i++)
    {
        curr = curr->next;
    }

    NODE* nodeToDelete = curr->next;
    curr->next = nodeToDelete->next;

    deleteNode(nodeToDelete);

    return root;
}

NODE *deleteLast(NODE *root)
{
    if (root->next == NULL)
    {
        deleteNode(root);
        root = NULL;

        return root;
    }
    NODE *curr = root;
    while (curr->next->next != NULL)
    {
        curr = curr->next; 
    }
    deleteNode(curr->next);
    curr->next = NULL;
    return root;
}

void printList(NODE *root)
{
    while (root != NULL)
    {
        printf("%d ", root->data);
        root = root->next;
    }
    printf("\n");
}

int main()
{
    NODE *root = createNode(1);
    root = insertFirst(root,0);
    root = insertLast(root,3);
    root = insertAnyPosition(root,2,2);
    root = insertLast(root,5);
    root = insertAnyPosition(root,4,4);
    for(int i=5; i>=0; i--)
    {
        //root = deleteAnyPosition(root,i);
        //root = deleteFirst(root);
        root = deleteLast(root);
        printList(root);
    }
    return 0;
}
