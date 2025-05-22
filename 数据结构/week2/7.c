#include "stdio.h"

int m, n;
int a[1000][1000];
int b[1000][1000];

struct Address
{
    int x, y;
} P[100000];

int isLegal(int i, int j)
{
    if (i <= 0 || i > m || j <= 0 || j > n || a[i][j] == 1 || b[i][j] == 1)
        return 0;
    return 1;
}

int findSolution(int i, int j, int now)
{
    P[now].x = i;
    P[now].y = j;
    if (i == m && j == n)
    {
        return now;
    }
    b[i][j] = 1;
    now++;
    if (isLegal(i + 1, j))
    {
        int p = findSolution(i + 1, j, now);
        if (p != 0)
            return p;
    }
    if (isLegal(i, j + 1))
    {
        int p = findSolution(i, j + 1, now);
        if (p != 0)
            return p;
    }
    if (isLegal(i - 1, j))
    {
        int p = findSolution(i - 1, j, now);
        if (p != 0)
            return p;
    }
    if (isLegal(i, j - 1))
    {
        int p = findSolution(i, j - 1, now);
        if (p != 0)
            return p;
    }
    return 0;
}

int main()
{
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &a[i][j]);
            b[i][j] = 0;
        }
    int result = findSolution(1, 1, 0);
    if (result != 0)
        for (int i = 0; i <= result; i++)
        {
            printf("<%d,%d> ", P[i].x, P[i].y);
        }
    else
        printf("There is no solution!");
    printf("\n");
    return 0;
}