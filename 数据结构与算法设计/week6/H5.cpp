#include <bits/stdc++.h>
#pragma warning(disable : 4996)
using namespace std;
int indegree[100];
int outdegree[100];
int testindegree[100];
int ve[100];
int vl[100];
int top[100][100];
int topo[55], path[100];
stack<int> T;
priority_queue<int, vector<int>, greater<int>> que[100]; // 这一步不必要，创建的原因是最初不知道先排序的思路时想到的一种排序方式
typedef struct node
{
    int adjvex;
    int weight;
    struct node *next;
} edgenode;

typedef struct vnode
{
    char vertex[10];
    edgenode *firsteage;
} vertexnode;

typedef struct
{
    vertexnode adjlist[100];
    int n, e;
} linkedgraph;
linkedgraph g;
// 上面三项是创建邻接表必不可少的
void creat(linkedgraph *g) // 建立邻接表，其中本题需要权值，若不需要权值也可通过此方式建立
{
    int i, j, k, weight;
    int flag1 = 0;
    int flag2 = 0;
    char f;
    char str[10000];
    memset(str, 0, sizeof(str));
    edgenode *s;
    scanf("%d,%d", &g->n, &g->e);
    getchar();
    cin >> str;
    int length = strlen(str);
    for (i = 0; i < length; i++)
    {
        if (str[i] != ',')
        {
            g->adjlist[flag1].vertex[flag2] = str[i];
            flag2++;
        }
        else
        {
            g->adjlist[flag1].vertex[flag2] = 0;
            g->adjlist[flag1].firsteage = NULL;
            flag2 = 0;
            flag1++;
        }
        g->adjlist[i].firsteage = NULL;
    }
    g->adjlist[flag1].vertex[flag2] = 0;
    for (k = 0; k < g->e; k++)
    {
        cin >> f >> i >> f >> j >> f >> weight >> f;
    L:
        char ah = getchar();

        s = (edgenode *)malloc(sizeof(edgenode));
        s->adjvex = j;
        s->weight = weight;
        s->next = g->adjlist[i].firsteage;
        g->adjlist[i].firsteage = s;
        if (ah == '\n')
            break;
        else if (ah == '<')
        {
            k++;
            cin >> i >> f >> j >> f >> weight >> f;
            goto L;
        }
    }
    edgenode *m, *n;
    for (k = 0; k < g->n; k++)
    { // 链表冒泡排序，目的是在临接路径中排好顺序，在输出时顺序就
        for (m = g->adjlist[k].firsteage; m != NULL; m = m->next)
            for (n = g->adjlist[k].firsteage; n != NULL; n = n->next)
                if (m->adjvex < n->adjvex)
                {
                    int t1 = m->adjvex;
                    m->adjvex = n->adjvex;
                    n->adjvex = t1;
                    int t2 = m->weight;
                    m->weight = n->weight;
                    n->weight = t2;
                }
    }
}
// 入度和出度测量~可以认为是度的测量
void inDegree(linkedgraph *g)
{
    edgenode *p;
    int i, outD;
    for (i = 0; i < g->n; i++)
    {
        outD = 0;
        p = g->adjlist[i].firsteage;
        while (NULL != p)
        {
            outD++;
            testindegree[p->adjvex]++;
            indegree[p->adjvex]++;
            p = p->next;
        }
        outdegree[i] = outD;
    }
}
// 第一次tp输出拓扑路径~参考《数据结构》
void ToplogicalSort(linkedgraph *g)
{
    priority_queue<int, vector<int>, greater<int>> S;
    edgenode *p;
    int i, k;
    int count = 0;
    for (i = 0; i < g->n; i++)
        if (!indegree[i])
            S.push(i);
    while (!S.empty())
    {
        i = S.top();
        S.pop();
        cout << g->adjlist[i].vertex;
        ++count;
        for (p = g->adjlist[i].firsteage; p != NULL; p = p->next)
        {
            k = p->adjvex;
            indegree[k]--;
            if (!indegree[k])
            {
                S.push(k);
            }
        }
        if (S.empty())
        {
            cout << endl;
        }
        else
            cout << "-";
    }
}
bool Toplogicalorder(linkedgraph *g) // 第二次TP，其实繁琐化了，完全可以并入第一个中
{
    stack<int> S;
    edgenode *p;
    int i, j, k;
    int count = 0;
    memset(ve, 0, sizeof(ve));
    for (i = 0; i < g->n; i++)
        if (!testindegree[i])
            S.push(i);
    while (!S.empty())
    {
        j = S.top();
        S.pop();
        T.push(j);
        topo[count] = j;
        ++count;
        for (p = g->adjlist[j].firsteage; p; p = p->next)
        {
            k = p->adjvex;
            if (--testindegree[k] == 0)
                S.push(k);
            if (ve[j] + p->weight > ve[k])
                ve[k] = ve[j] + p->weight;
        }
    }
    if (count < g->n)
    {
        return false;
    }
    else
        return true;
}
void printpath(int top, int end, linkedgraph *g) // 递归输出法
{
    int ee, el, k, dut;
    edgenode *p;
    int u = path[top - 1];
    if (u == end)
    {
        cout << g->adjlist[path[0]].vertex;
        for (int i = 1; i < top; i++)
            printf("-%s", g->adjlist[path[i]].vertex);
        printf("\n");
        return;
    }
    for (p = g->adjlist[u].firsteage; p != NULL; p = p->next)
    {
        k = p->adjvex;
        dut = p->weight;
        ee = ve[u];
        el = vl[k] - dut;
        if (ee == el)
        {
            path[top++] = k;
            printpath(top, end, g);
            top--;
        }
    }
}
void CriticalPath(linkedgraph *g) // 还是参见《数据结构》
{
    edgenode *p;
    int i, j, k, dut, ee, el;
    char tag;
    for (i = 0; i < g->n; i++)
        vl[i] = ve[g->n - 1];
    while (!T.empty())
        for (j = T.top(), T.pop(), p = g->adjlist[j].firsteage; p != NULL; p = p->next)
        {
            k = p->adjvex;
            dut = p->weight;
            if (vl[k] - dut < vl[j])
                vl[j] = vl[k] - dut;
        }
    path[0] = topo[0]; // path其实不必要
    printpath(1, topo[g->n - 1], g);
}
int main()
{
    creat(&g);
    inDegree(&g);
    if (Toplogicalorder(&g) == false)
    {
        cout << "NO TOPOLOGICAL PATH" << endl;
        return 0;
    }
    ToplogicalSort(&g);
    CriticalPath(&g);
    return 0;
}
