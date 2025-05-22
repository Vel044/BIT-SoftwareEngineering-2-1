#include <cstdio>
#include <stack>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

// 定义三元组和顺序表
typedef struct
{
    int i, j;
    int e;
} Triple;

typedef struct
{
    Triple data[1000];
    int rpos[1000];
    int mu, nu, tu;
} RLSMatrix;

int rpos[1000];
int num[1000];

int main()
{
    int arow = 0, brow = 0, tp = 0;
    int col = 0, ccol = 0;
    int p = 0, t = 0, q = 0;
    RLSMatrix M, N, Q;

    // 输入M、N矩阵数据
    scanf("%d %d %d", &M.mu, &M.nu, &M.tu);
    for (int i = 1; i <= M.tu; i++)
        scanf("%d %d %d", &M.data[i].i, &M.data[i].j, &M.data[i].e);
    scanf("%d %d %d", &N.mu, &N.nu, &N.tu);
    for (int i = 1; i <= N.tu; i++)
        scanf("%d %d %d", &N.data[i].i, &N.data[i].j, &N.data[i].e);

    for (col = 1; col <= M.mu; col++)
        num[col] = 0;
    for (int i = 1; i <= M.tu; i++)
        num[M.data[i].i]++;
    M.rpos[1] = 1;
    for (col = 2; col <= M.mu; col++)
        M.rpos[col] = M.rpos[col - 1] + num[col - 1];
    for (col = 1; col <= N.mu; col++)
        num[col] = 0;
    for (int i = 1; i <= N.tu; i++)
        num[N.data[i].i]++;
    N.rpos[1] = 1;
    for (col = 2; col <= N.mu; col++)
        N.rpos[col] = N.rpos[col - 1] + num[col - 1];

    /* 计算矩阵乘积 */
    Q.mu = M.mu;
    Q.nu = N.nu;
    Q.tu = 0;
    if (M.tu * N.tu != 0)
    {
        for (arow = 1; arow <= M.mu; arow++)
        {
            memset(rpos, 0, sizeof(rpos));
            Q.rpos[arow] = Q.tu + 1;
            if (arow < M.mu)
                tp = M.rpos[arow + 1];
            else
                tp = M.tu + 1;
            for (p = M.rpos[arow]; p < tp; p++)
            {
                brow = M.data[p].j;
                if (brow < N.mu)
                    t = N.rpos[brow + 1];
                else
                    t = N.tu + 1;
                for (q = N.rpos[brow]; q < t; q++)
                {
                    ccol = N.data[q].j;
                    rpos[ccol] += M.data[p].e * N.data[q].e;
                }
            }
            for (ccol = 1; ccol <= Q.nu; ccol++)
            {
                if (rpos[ccol])
                {
                    Q.tu++;
                    Q.data[Q.tu].i = arow;
                    Q.data[Q.tu].j = ccol;
                    Q.data[Q.tu].e = rpos[ccol];
                }
            }
        }
    }

    // 输出乘积矩阵Q
    printf("%d\n", Q.mu);
    printf("%d\n", Q.nu);
    printf("%d\n", Q.tu);

    for (int i = 1; i <= Q.tu; i++)
        printf("%d,%d,%d\n", Q.data[i].i, Q.data[i].j, Q.data[i].e);

    return 0;
}
