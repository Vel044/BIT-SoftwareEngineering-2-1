#include <bits/stdc++.h>
using namespace std;
const int Max = 100;
struct Edge
{
    int n1, n2, value;
};
bool cmp(Edge e1, Edge e2)
{
    return e1.value < e2.value;
}
class UnionFindSet
{
private:
    vector<int>parent,rank;
public:
    UnionFindSet(int n)
    {
        for (int i = 0; i <= n; i++)
        {
            parent.push_back(i);
            rank.push_back(1);
        }
    }
    int find(int x)
    {
        if (x == parent[x])
            return x;
        else
            return parent[x] = find(parent[x]);
    }
    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }
    void unite(int x, int y)
    {
        int xparent = find(x);
        int yparent = find(y);
        if (xparent == yparent)
            return;
        if (rank[xparent] >= rank[yparent])
        {
            parent[yparent] = xparent;
            rank[xparent] += rank[yparent];
        }
        else
        {
            parent[xparent] = yparent;
            rank[yparent] += rank[xparent];
        }
    }
};
class Graph
{
private:
    int N, M;
    Edge E[Max];
public:
    Graph(int n,int m)
    {
        N = n;
        M = m;
        for (int i = 0; i < M; i++)
        {
            cin >> E[i].n1 >> E[i].n2 >> E[i].value;
        }
    }
    void kruskal()
    {
        int sum = 0;
        if (M == 0)
        {
            cout << "0 " << endl;
            return;
        }
        vector<Edge>mst;
        UnionFindSet U(N);
        sort(E, E + M, cmp);
        for (int i = 0; i < M; i++)
        {
            if (mst.size() == N - 1)
                break;
            if (!U.connected(E[i].n1, E[i].n2))
            {
                mst.push_back(E[i]);
                sum += E[i].value;
                U.unite(E[i].n1, E[i].n2);
            }
        }
        if (mst.size() < N - 1)
        {
            cout << "-1" << endl;
        }
        else
        {
            cout << sum << endl;
        }
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    Graph G(n, m);
    G.kruskal();
    return 0;
}
