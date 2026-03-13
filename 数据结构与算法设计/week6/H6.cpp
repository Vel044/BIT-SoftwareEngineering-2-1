#include <iostream>
#include <queue>
using namespace std;

int Map[1000][1000] = {0};
int vir[1000][1000] = {0};
int m, n, stx, sty, edx, edy;
int trend[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // 0-下，1-上，2-右，3-左
struct node
{
    int x, y; // 坐标
    int dir;  // 方向
    int turn; // 转弯次数
};
void BFS()
{
    queue<node> q;
    node k0, k1, t0;
    int flag = 0;
    for (int i = 0; i < 4; i++)
    {
        t0.x = stx + trend[i][0];
        t0.y = sty + trend[i][1];
        t0.dir = i;
        t0.turn = 1;
        vir[t0.x][t0.y] = t0.turn;
        q.push(t0);
    }
    while (!q.empty())
    {
        k0 = q.front();
        q.pop();
        if (k0.x == edx && k0.y == edy)
        {
            flag = 1;
            cout << "TRUE" << endl;
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            k1.x = k0.x + trend[i][0];
            k1.y = k0.y + trend[i][1];
            k1.dir = i;
            if (k1.dir != k0.dir)
                k1.turn = k0.turn + 1;
            else
                k1.turn = k0.turn;
            if (k1.turn > 3 || k1.x < 0 || k1.y < 0 || k1.x > m - 1 || k1.y > n - 1)
                continue;
            if (Map[k1.x][k1.y] != 0 && Map[k1.x][k1.y] != Map[edx][edy])
                continue;
            if (vir[k1.x][k1.y] == 0 || vir[k1.x][k1.y] >= k1.turn)
            {
                vir[k1.x][k1.y] = k1.turn;
                q.push(k1);
            }
        }
    }
    if (!flag)
        cout << "FALSE" << endl;
}
int main()
{
    cin >> m >> n;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> Map[i][j];
    cin >> stx >> sty >> edx >> edy;
    BFS();

    return 0;
}