//
// Created by LittleCat on 2020/3/10.
//

#include <cstdio>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;
#define MAX 1550

vector<int> point[MAX]; // map[i]储存节点i的临接节点集
bool vis[MAX];          // vis[i]表示节点i是否被访问过
int dp[MAX][2];

void DFS(int root)
{
    vis[root] = true; // 标记已访问节点
    /* 依次遍历根节点的每一个子节点 */
    for (int i = 0; i < point[root].size(); i++)
    {
        int next = point[root][i]; // 子节点
        if (vis[next])             // 是已访问的前驱节点
            continue;              // 避免往回搜索
        DFS(next);                 // 搜索子节点
        dp[root][0] += dp[next][1];
        dp[root][1] += min(dp[next][0], dp[next][1]);
    }
    dp[root][1]++;
}

int main()
{
    int n;
    while (EOF != scanf("%d", &n))
    {
        /* 初始化数组 */
        for (auto &i : point)
            i.clear();
        memset(vis, false, sizeof(vis));
        memset(dp, 0, sizeof(dp));
        /* 处理输入 */
        for (int i, k; n; n--)
        {
            scanf("%d:(%d)", &i, &k); // 前驱节点i,边数k
            for (int j; k; k--)
            {
                scanf("%d", &j); // 后继节点j
                point[i].push_back(j);
                point[j].push_back(i);
            }
        }
        int root = 0;
        DFS(root);
        printf("%d\n", min(dp[root][0], dp[root][1]));
    }
}