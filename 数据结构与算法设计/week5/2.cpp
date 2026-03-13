#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode
{
    char val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Queue
{
    TreeNode *data[100];
    int head, tail;
} Queue;

Queue *init_queue(int n)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->head = q->tail = 0;
    return q;
}

TreeNode *init_tree(char val)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

int empty(Queue *q)
{
    return q->head == q->tail;
}

void push(Queue *q, TreeNode *node)
{
    q->data[q->tail++] = node;
}

TreeNode *front(Queue *q)
{
    return q->data[q->head];
}

void pop(Queue *q)
{
    if (!empty(q))
        ++q->head;
}

TreeNode *build(char *inorder, char *postorder, int len)
{
    if (len == 0)
        return NULL;
    TreeNode *node = init_tree(postorder[len - 1]);
    int pos = strchr(inorder, postorder[len - 1]) - inorder;
    node->left = build(inorder, postorder, pos);
    node->right = build(inorder + pos + 1, postorder + pos, len - pos - 1);
    return node;
}

void output(TreeNode *root)
{
    if (root == NULL)
        return;
    Queue *q = init_queue(100);
    push(q, root);
    while (!empty(q))
    {
        TreeNode *temp_node = front(q);
        printf("%c", temp_node->val);
        pop(q);
        if (temp_node->left != NULL)
            push(q, temp_node->left);
        if (temp_node->right != NULL)
            push(q, temp_node->right);
    }
}

int main()
{
    char inorder[50], postorder[50];
    scanf("%s%s", inorder, postorder);
    TreeNode *root = build(inorder, postorder, strlen(inorder));
    output(root);
    printf("\n");
    return 0;
}
