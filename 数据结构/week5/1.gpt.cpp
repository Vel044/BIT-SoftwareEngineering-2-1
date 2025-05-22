#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

// 二叉树的存储表示
typedef struct TreeNode
{
    char data;
    struct TreeNode *leftChild;
    struct TreeNode *rightChild;
} TreeNode, *Tree;

queue<Tree> q; // 辅助队列
int leafCount = 0;  // 统计叶子结点数目

void createTree();          // 建立二叉树
void visit(Tree R);         // 访问结点
void print(Tree R, int n);  // 输出二叉树
void preOrder(Tree R);  // 先序遍历
void inOrder(Tree R);   // 中序遍历
void postOrder(Tree R); // 后序遍历
/* 左右子树交换后的各种表示 */
void swapPrint(Tree R, int n);
void swapPreOrder(Tree R);
void swapInOrder(Tree R);
void swapPostOrder(Tree R);

int main()
{
    Tree tree;
    tree = (Tree)malloc(sizeof(TreeNode));
    q.push(tree);

    // 建树
    createTree();

    // 打印二叉树
    printf("Tree\n");
    print(tree, 0);

    // 先序
    printf("preOrder  : ");
    preOrder(tree);
    printf("\n");

    // 中序
    printf("inOrder   : ");
    inOrder(tree);
    printf("\n");

    // 后序
    printf("postOrder : ");
    postOrder(tree);
    printf("\n");

    // 叶子结点数目
    printf("Number of leaf: %d\n", leafCount);

    /* 翻转 */
    printf("Tree swapped\n");
    swapPrint(tree, 0);

    printf("preOrder  : ");
    swapPreOrder(tree);
    printf("\n");

    printf("inOrder   : ");
    swapInOrder(tree);
    printf("\n");

    printf("postOrder : ");
    swapPostOrder(tree);
    printf("\n");

    return 0;
}

void createTree()
{
    char c;
    Tree T, N;
    while (!q.empty())
    {
        scanf("%c", &c);
        if (c == '\n') // 换行符结束读取
            break;

        T = q.front();
        q.pop();
        T->data = c; // 结点赋值

        // 左子树表示
        N = (Tree)malloc(sizeof(TreeNode));
        N->data = '\0';
        T->leftChild = N;
        q.push(N);

        // 右子树表示
        N = (Tree)malloc(sizeof(TreeNode));
        N->data = '\0';
        T->rightChild = N;
        q.push(N);
    }
}
void visit(Tree R)
{
    // 结点不为空则输出
    if (R->data != '#' && R->data != '\0')
        cout << R->data;
}
void print(Tree R, int n)
{
    if (R->data != '#' && R->data != '\0')
    {
        int i = 1;
        while (i <= n) // 第几层就输几个tab
        {
            cout << "    ";
            i++;
        }
        visit(R);
        cout << endl;

        // 一层一层往下找
        n++;
        print(R->leftChild, n);
        print(R->rightChild, n);
    }
}
void preOrder(Tree R)
{
    if (R->data != '#' && R->data != '\0')
    {
        visit(R);
        preOrder(R->leftChild);
        preOrder(R->rightChild);
    }
}
void inOrder(Tree R)
{
    if (R->data != '#' && R->data != '\0')
    {
        inOrder(R->leftChild);

        /* 统计叶子结点和中序遍历结合 */
        if ((R->leftChild->data == '#' || R->leftChild->data == '\0') && (R->rightChild->data == '#' || R->rightChild->data == '\0'))
            leafCount++;

        visit(R);
        inOrder(R->rightChild);
    }
}
void postOrder(Tree R)
{
    if (R->data != '#' && R->data != '\0')
    {
        postOrder(R->leftChild);
        postOrder(R->rightChild);
        visit(R);
    }
}
void swapPrint(Tree R, int n)
{
    // 翻转后的写法与原来一模一样，只是换了顺序而已
    if (R->data != '#' && R->data != '\0')
    {
        int i = 1;
        while (i <= n)
        {
            cout << "    ";
            i++;
        }
        visit(R);
        cout << endl;

        n++;
        swapPrint(R->rightChild, n);
        swapPrint(R->leftChild, n);
    }
}
void swapPreOrder(Tree R)
{
    if (R->data != '#' && R->data != '\0')
    {
        visit(R);
        swapPreOrder(R->rightChild);
        swapPreOrder(R->leftChild);
    }
}
void swapInOrder(Tree R)
{
    if (R->data != '#' && R->data != '\0')
    {
        swapInOrder(R->rightChild);
        visit(R);
        swapInOrder(R->leftChild);
    }
}
void swapPostOrder(Tree R)
{
    if (R->data != '#' && R->data != '\0')
    {
        swapPostOrder(R->rightChild);
        swapPostOrder(R->leftChild);
        visit(R);
    }
}
