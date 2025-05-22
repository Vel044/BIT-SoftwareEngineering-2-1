#include <stdio.h>
#include <stdlib.h>

struct BinaryTreeNode
{
    char element;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};
typedef struct BinaryTreeNode *NodePtr;
int leafCount;

void createBinaryTree(NodePtr *rootPtr) // 用二级指针创建二叉树
{
    char c;
    c = getchar();
    if (c == '#')
        *rootPtr = NULL;
    else
    {
        (*rootPtr) = (NodePtr)malloc(sizeof(struct BinaryTreeNode));
        (*rootPtr)->element = c;
        createBinaryTree(&(*rootPtr)->left);
        createBinaryTree(&(*rootPtr)->right);
        if (!(*rootPtr)->left && !(*rootPtr)->right)
            leafCount++;
    }
}

NodePtr createBTree(NodePtr root) // 用返回值创建二叉树（没用二级指针）
{

    char c;
    c = getchar();
    if (root == NULL && c != '#')
    {
        root = (NodePtr)malloc(sizeof(struct BinaryTreeNode));
        root->element = c;
        root->left = root->right = NULL;
        root->left = createBTree(root->left);
        root->right = createBTree(root->right);
        if (!(root)->left && !(root)->right)
            leafCount++;
    }
    return root;
}

void inOrderTraversal(NodePtr root)
{
    if (root)
    {
        inOrderTraversal(root->left);
        printf("%c", root->element);
        inOrderTraversal(root->right);
    }
}

void preOrderTraversal(NodePtr root)
{
    if (root)
    {
        printf("%c", root->element);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void postOrderTraversal(NodePtr root)
{
    if (root)
    {

        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%c", root->element);
    }
}

void printLine(char c, int num)
{
    for (int i = 0; i < 4 * num; i++)
    {
        printf(" ");
    }
    printf("%c\n", c);
}

void listTree(NodePtr root, int depth)
{
    if (root)
    {
        printLine(root->element, depth);
        listTree(root->left, depth + 1);
        listTree(root->right, depth + 1);
    }
}

void swapChildren(NodePtr root)
{
    if (root)
    {

        if (root->left || root->right)
        {
            NodePtr temp = root->left;
            root->left = root->right;
            root->right = temp;
            if (root->left)
                swapChildren(root->left);
            if (root->right)
                swapChildren(root->right);
        }
    }
}
int main()
{

    NodePtr rootNode = NULL;

    printf("BiTree\n");
    rootNode = createBTree(rootNode);
    listTree(rootNode, 0);

    printf("pre_sequence  : ");
    preOrderTraversal(rootNode);
    printf("\n");
    printf("in_sequence   : ");
    inOrderTraversal(rootNode);
    printf("\n");
    printf("post_sequence : ");
    postOrderTraversal(rootNode);
    printf("\n");

    printf("Number of leaf: %d\n", leafCount);
    printf("BiTree swapped\n");
    swapChildren(rootNode);
    listTree(rootNode, 0);

    printf("pre_sequence  : ");
    preOrderTraversal(rootNode);
    printf("\n");
    printf("in_sequence   : ");
    inOrderTraversal(rootNode);
    printf("\n");
    printf("post_sequence : ");
    postOrderTraversal(rootNode);
    printf("\n");

    return 0;
}
