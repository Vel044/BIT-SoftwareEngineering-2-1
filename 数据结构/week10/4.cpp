#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
int dp_max[207][207];
int dp_min[207][207];
int cost[207];
int a[203];
const int MAX = 0x3f3f3f3f;

int main()
{
    while (scanf("%d", &n) != EOF)
    {
        memset(dp_min, MAX, sizeof(dp_min));
        memset(dp_max, 0, sizeof(dp_max));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
            a[i + n] = a[i];
            dp_min[i][i] = 0;
            dp_min[i + n][i + n] = 0;
        }
        cost[0] = 0;

        for (int i = 1; i <= 2 * n; i++) // 为了后面方便用前缀和
            cost[i] = cost[i - 1] + a[i];

        for (int len = 2; len <= n; len++) // 走几步
        {
            for (int i = 1; len + i - 1 <= 2 * n; i++) // 从哪开始
            {
                int j = len + i - 1;
                for (int k = i; k < j; k++)
                {
                    dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] + dp_min[k + 1][j] + cost[j] - cost[i - 1]);
                    dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] + dp_max[k + 1][j] + cost[j] - cost[i - 1]);
                }
            }
        }
        int ans_min = MAX;
        int ans_max = -1;
        for (int i = 1; i <= n; i++)
        {
            ans_min = min(ans_min, dp_min[i][i + n - 1]);
            ans_max = max(ans_max, dp_max[i][i + n - 1]);
        }
        cout << ans_min << endl << ans_max << endl;
    }
    return 0;
}
