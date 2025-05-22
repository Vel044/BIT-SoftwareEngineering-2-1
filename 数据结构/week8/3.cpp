#include <bits/stdc++.h>

#define MAX_SIZE 2000005
#define OK 1
#define ERROR 0

using namespace std;

const int INF = 0x3f3f3f3f;
typedef long long ll;

int all[MAX_SIZE];
int select(int l, int r, int k);
int insertSort3(int x);
int Partition(int l, int r, int p);

int main()
{

    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    int a, b, n = 0;
    while (scanf("%d,%d", &a, &b) != EOF)
    { // 输入数据
        all[n++] = b;
    }

    if (n % 2 == 1)
    {
        cout << select(0, n - 1, (n + 1) / 2) << endl;
    }
    else
    {
        cout << select(0, n - 1, n / 2) << endl;
    }

    return 0;
}

int select(int l, int r, int k)
{ // l为数组左下标，r为数组右下标，k为要找的第k小的数

    if (r - l < 75)
    { // 如果长度小于75直接排序并返回第k小的值
        sort(all + l, all + r + 1);
        return all[l + k - 1];
    }

    for (int i = 0; i <= (r - l - 4) / 5; i++)
    {
        insertSort3(l + 5 * i);
        swap(all[l + i], all[l + 5 * i + 2]);
    }

    int mid = select(l, l + (r - l - 4) / 5, (r - l - 4) / 10); // 递归寻找中位数的值，即为k = (r - l - 4) / 10

    int i = Partition(l, r, mid);
    int len = i - l + 1;

    if (len == k)
    {
        return all[i];
    }
    else if (k < len)
    {
        return select(l, i - 1, k);
    }
    else
    {
        return select(i + 1, r, k - len);
    }
}

int insertSort3(int x)
{ // 选择查找第三小的数

    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (all[x + j] > all[x + i])
            {
                swap(all[x + j], all[x + i]);
            }
        }
    }

    return 0;
}

int Partition(int l, int r, int p)
{

    int i, j;
    for (i = l; i <= r; i++)
    {
        if (p == all[i])
        {
            swap(all[i], all[l]);
            break;
        }
    }

    i = l, j = r + 1;
    while (1)
    {
        while (all[++i] < p && i < r)
            ;
        while (all[--j] > p)
            ;
        if (i >= j)
            break;
        swap(all[i], all[j]);
    }
    all[l] = all[j];
    all[j] = p;

    return j;
}
