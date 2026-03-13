#include <cstdio>
#include <stack>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;


typedef struct
{
    int row, col, val;
} Triple;

typedef struct
{
    Triple data[1000];
    int rpos[1000];
    int rows, cols, nonzeros;
} SparseMatrix;

int rpos[1000];
int num[1000];


int main()
{
    int arow = 0, brow = 0, tp = 0;
    int col = 0, ccol = 0;
    int p = 0, t = 0, q = 0;
    SparseMatrix M, N, Q;

    // 输入M、N矩阵数据
    scanf("%d%d%d", &M.rows, &M.cols, &M.nonzeros);
    for (int i = 1; i <= M.nonzeros; i++)
        scanf("%d%d%d", &M.data[i].row, &M.data[i].col, &M.data[i].val);
    scanf("%d%d%d", &N.rows, &N.cols, &N.nonzeros);
    for (int i = 1; i <= N.nonzeros; i++)
        scanf("%d%d%d", &N.data[i].row, &N.data[i].col, &N.data[i].val);

    for (col = 1; col <= M.rows; col++)
        num[col] = 0;
    for (int i = 1; i <= M.nonzeros; i++)
        num[M.data[i].row]++;
    M.rpos[1] = 1;
    for (col = 2; col <= M.rows; col++)
        M.rpos[col] = M.rpos[col - 1] + num[col - 1];
    for (col = 1; col <= N.rows; col++)
        num[col] = 0;
    for (int i = 1; i <= N.nonzeros; i++)
        num[N.data[i].row]++;
    N.rpos[1] = 1;
    for (col = 2; col <= N.rows; col++)
        N.rpos[col] = N.rpos[col - 1] + num[col - 1];

    /* 计算矩阵乘积 */
    Q.rows = M.rows;
    Q.cols = N.cols;
    Q.nonzeros = 0;
    if (M.nonzeros * N.nonzeros != 0)
    {
        for (arow = 1; arow <= M.rows; arow++)
        {
            memset(rpos, 0, sizeof(rpos));
            Q.rpos[arow] = Q.nonzeros + 1;
            if (arow < M.rows)
                tp = M.rpos[arow + 1];
            else
                tp = M.nonzeros + 1;
            for (p = M.rpos[arow]; p < tp; p++)
            {
                brow = M.data[p].col;
                if (brow < N.rows)
                    t = N.rpos[brow + 1];
                else
                    t = N.nonzeros + 1;
                for (q = N.rpos[brow]; q < t; q++)
                {
                    ccol = N.data[q].col;
                    rpos[ccol] += M.data[p].val * N.data[q].val;
                }
            }
            for (ccol = 1; ccol <= Q.cols; ccol++)
            {
                if (rpos[ccol])
                {
                    Q.nonzeros++;
                    Q.data[Q.nonzeros].row = arow;
                    Q.data[Q.nonzeros].col = ccol;
                    Q.data[Q.nonzeros].val = rpos[ccol];
                }
            }
        }
    }

    // 输出乘积矩阵Q
    printf("%d\n", Q.rows);
    printf("%d\n", Q.cols);
    printf("%d\n", Q.nonzeros);
    for (int i = 1; i <= Q.nonzeros; i++)
        printf("%d,%d,%d\n", Q.data[i].row, Q.data[i].col, Q.data[i].val);

    return 0;
}