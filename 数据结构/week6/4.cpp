#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int m = 1e6 + 5;
int n;
int a[m], b[m];
bool cmp(int z, int y)
{
    return z < y;
}
int main()
{
    int ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &a[i], &b[i]);
    }
    sort(a, a + n, cmp); // 活动开始时间
    sort(b, b + n, cmp); // 活动结束时间
    int cal = 0;
    for (int i = 0, j = 0; i < n;)
    {
        if (a[i] < b[j])
        {
            cal++;
            i++;
        }
        else // 开始时间结束时间相等，先处理结束时间
        {
            cal--;
            j++;
        }
        if (ans < cal)
            ans = cal;
    }
    cout << ans << endl;
    return 0;
}