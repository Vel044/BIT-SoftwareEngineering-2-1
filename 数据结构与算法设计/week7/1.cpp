
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e6 + 5;
int n, a[N], b[N], s = 0, flag = 1;

void bs(int l, int r)
{
    int mid = (l + r) / 2;
    if (l <= r)
    {
        if (a[mid] == mid)
        {
            b[s] = mid;
            s++;
            bs(l, mid - 1);
            bs(mid + 1, r);
        }
        else if (a[mid] < mid)
        {
            if (flag)
                bs(mid + 1, r);
            else
                bs(l, mid - 1);
        }
        else if (a[mid] > mid)
        {
            if (flag)
                bs(l, mid - 1);
            else
                bs(mid + 1, r);
        }
    }
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    if (a[0] > a[n - 1])
        flag = 0;
    bs(0, n - 1);
    if (s > 0)
    {
        sort(b, b + s);
        for (int i = 0; i < s; i++)
            printf("%d ", b[i]);
        printf("\n");
    }
    else
        printf("No \n");
}