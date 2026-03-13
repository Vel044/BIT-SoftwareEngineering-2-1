#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

int weights[1000000];     // 集装箱的重量
int numBoxes;          // 集装箱的数量
int maxLoad = 0;       // 船的最大载重量
int bestLoad = 0;      // 最优解的载重量
int foundSolution = 0; // 是否找到了最优解
int boxIndices[1000000];  // 装入货物的下标

typedef struct node
{
    int weight;         // 节点的重量
    struct node *left;  // 左孩子节点
    struct node *right; // 右孩子节点
} NODE;

void initializeNode(NODE *node)
{
    node->left = NULL;
    node->right = NULL;
    node->weight = 0;
}

void createTree(NODE *&node, int depth)
{
    if (depth > numBoxes)
        return;
    if (node->left == NULL)
    {
        NODE *newNode;
        newNode = (NODE *)malloc(sizeof(NODE));
        initializeNode(newNode);
        node->left = newNode;
        createTree(newNode, depth + 1);
    }
    if (node->right == NULL)
    {
        NODE *newNode;
        newNode = (NODE *)malloc(sizeof(NODE));
        initializeNode(newNode);
        node->right = newNode;
        newNode->weight = weights[depth];
        createTree(newNode, depth + 1);
    }
}

int totalMax(NODE *node, int sum)
{
    while (node)
    {
        sum += node->weight;
        node = node->right;
    }
    return sum;
}

void dfs(NODE *node, int i, int sum)
{
    if (foundSolution)
        return;

    if (node->left == node->right)
    {
        boxIndices[i] = node->weight;
        sum += node->weight;

        if (sum == maxLoad)
        {
            bestLoad = sum;
            foundSolution = 1;
        }
        else if (sum < maxLoad)
        {
            if (bestLoad < sum)
                bestLoad = sum;
        }
        return;
    }
    else
    {
        boxIndices[i] = node->weight;
        sum += node->weight;
        if (sum == maxLoad)
        {
            bestLoad = sum;
            foundSolution = 1;
            return;
        }
        if (sum > maxLoad)
        {
            return;
        }
        if (totalMax(node->right, sum) <= bestLoad)
            return;

        dfs(node->right, i + 1, sum);
        dfs(node->left, i + 1, sum);
    }
}

int main()
{
    int i;

    cin >> maxLoad;
    cin >> numBoxes;

    memset(weights, 0, sizeof(weights));
    memset(boxIndices, -1, sizeof(boxIndices));

    for (i = 1; i <= numBoxes; i++)
    {
        cin >> weights[i];
    }

    NODE *root;
    root = (NODE *)malloc(sizeof(NODE));

    initializeNode(root);

    createTree(root, 1);

    dfs(root, 0, 0);

    cout << bestLoad << endl;

    i = 0;

    while (boxIndices[i] != -1)
    {

        if (boxIndices[i])
            cout << i << " ";

        i++;
    }
    cout << endl;

    return 0;
}
