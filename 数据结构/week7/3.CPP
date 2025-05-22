#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct node
{
    int height;
    char data;
    struct node *lchild, *rchild;
} AVLNode, *AVLTree;

int Height(AVLTree T)
{
    if (!T)
        return -1;
    return T->height;
}

AVLTree LL(AVLTree k2)
{

    AVLTree k1;
    k1 = k2->lchild;
    k2->lchild = k1->rchild;
    k1->rchild = k2;
    k1->height = max(Height(k1->lchild), Height(k1->rchild)) + 1;
    k2->height = max(Height(k2->lchild), Height(k2->rchild)) + 1;
    return k1;
}

AVLTree RR(AVLTree k2)
{
    AVLTree k1;
    k1 = k2->rchild;
    k2->rchild = k1->lchild;
    k1->lchild = k2;
    k1->height = max(Height(k1->lchild), Height(k1->rchild)) + 1;
    k2->height = max(Height(k2->lchild), Height(k2->rchild)) + 1;
    return k1;
}

AVLTree LR(AVLTree K3)
{
    K3->lchild = RR(K3->lchild);
    return LL(K3);
}

AVLTree RL(AVLTree K3)
{
    K3->rchild = LL(K3->rchild);
    return RR(K3);
}

AVLTree insert(char data, AVLTree T)
{
    if (T == NULL)
    {
        T = (AVLTree)malloc(sizeof(AVLNode));
        T->data = data;
        T->height = 0;
        T->lchild = T->rchild = NULL;
    }
    else if (data < T->data)
    {
        T->lchild = insert(data, T->lchild);
        if (Height(T->lchild) - Height(T->rchild) == 2)
        {
            if (data < T->lchild->data)
                T = LL(T);
            else
                T = LR(T);
        }
    }
    else if (data > T->data)
    {
        T->rchild = insert(data, T->rchild);
        if (Height(T->rchild) - Height(T->lchild) == 2)
        {
            if (data > T->rchild->data)
                T = RR(T);
            else
                T = RL(T);
        }
    }
    T->height = max(Height(T->lchild), Height(T->rchild)) + 1;
    return T;
}

void preorder(AVLTree t)
{
    if (t)
    {
        printf("%c", t->data);
        preorder(t->lchild);
        preorder(t->rchild);
    }
}

void inorder(AVLTree t)
{
    if (t)
    {
        inorder(t->lchild);
        printf("%c", t->data);
        inorder(t->rchild);
    }
}

void postorder(AVLTree t)
{
    if (t)
    {
        postorder(t->lchild);
        postorder(t->rchild);
        printf("%c", t->data);
    }
}

void print(AVLTree t, int depth)
{
    if (t)
    {
        if (t->rchild)
            print(t->rchild, depth + 1);
        for (int i = 0; i < depth; i++)
            printf("    ");
        printf("%c\n", t->data);
        if (t->lchild)
            print(t->lchild, depth + 1);
    }
}

int main()
{
    char tree[50];
    gets(tree);
    AVLTree root = NULL;
    for (int i = 0; tree[i]; i++)
    {
        root = insert(tree[i], root);
    }
    printf("Preorder: ");
    preorder(root);
    printf("\n");
    printf("Inorder: ");
    inorder(root);
    printf("\n");
    printf("Postorder: ");
    postorder(root);
    printf("\n");
    printf("Tree:\n");
    print(root, 0);
    return 0;
}