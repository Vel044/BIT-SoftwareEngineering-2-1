#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const double inf = 1e20;
struct point
{
	double x, y;
} p[100005], t[100005];
bool cmpxy(point a, point b) // 按照x从小到大，x相等y从小到大排序
{
	if (a.x != b.x)
	{
		return a.x < b.x;
	}
	else
	{
		return a.y < b.y;
	}
}
bool cmpy(point a, point b)
{
	return a.y < b.y;
}
double dist(point a, point b)
{
	double sum = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	return 1.0 * sqrt(sum);
}
double search(int left, int right)
{
	if (left == right)
		return inf;
	if (right - left == 1)
		return dist(p[left], p[right]);
	int mid = (left + right) / 2;
	double d1 = search(left, mid);		// 左半区间最小值
	double d2 = search(mid + 1, right); // 右半区间最小值
	double d = min(d1, d2);
	int k = 0;
	for (int i = left; i <= right; i++)
	{
		if (fabs(p[i].x - p[mid].x) <= d)
		{
			t[k++] = p[i];
		}
	}
	sort(t, t + k, cmpy);
	for (int i = 0; i < k; i++)
	{
		for (int j = i + 1; j < k; j++)
		{
			if (t[j].y - t[i].y >= d)
				break; // 乐观剪枝，y的差值已经超过d就没有计算意义
			d = min(d, dist(t[i], t[j]));
		}
	}
	return d;
}
int main()
{
	int n;
	while (~scanf("%d", &n) && n)
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%lf%lf", &p[i].x, &p[i].y);
		}
		sort(p, p + n, cmpxy);
		double ans = search(0, n - 1) / 2;
		printf("%.2f\n", ans);
	}
	return 0;
}
