#include <cstdio>
#include <cstring>
int a[2005], m[2005][2005], s[2005][2005];
const int inf = 2147483647;
void traceback(int i, int j) // 递归输出最优解的函数
{
    if (i == j) // 递归边界条件，此时应该打印了
    {
        printf("A%d", i);
        return;
    }
    printf("(");
    traceback(i, s[i][j]);
    traceback(s[i][j] + 1, j);
    printf(")");
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int r = 2; r <= n; r++) // r为矩阵链的长度
    {
        for (int i = 1; i <= n - r + 1; i++) // 从Ai开始的矩阵链
        {
            int j = i + r - 1; // 矩阵链的最后一个矩阵下标
            m[i][j] = inf;
            for (int k = i; k < j; k++) // 枚举k的位置
            {
                int t = m[i][k] + m[k + 1][j] + a[i - 1] * a[k] * a[j];
                if (t < m[i][j])
                {
                    m[i][j] = t;
                    s[i][j] = k; // s存的是计算A[i:j]的最优解中矩阵链断开的位置
                }
            }
        }
    }
    printf("%d\n", m[1][n]); // 输出最优值
    if (n == 1)
        printf("(A1)"); // 特判
    else
        traceback(1, n); // 输出最优解
    printf("\n");
    return 0;
}
