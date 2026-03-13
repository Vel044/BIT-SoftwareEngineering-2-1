#include <iostream>
#include <vector>

using namespace std;

void josephus(int n, int k, int m)
{
    if (n <= 0 || k <= 0 || m <= 0)
    {
        cout << "n,m,k must bigger than 0." << endl;
        return;
    }
    if (k > n)
    {
        cout << "k should not bigger than n." << endl;
        return;
    }
    int a[100000];
    for (int i = 0; i < n; i++)
    {
        a[i] = i + 1;
    }
    int now = k - 1; // 当前几号
    int out = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m;) // 数到j
        {
            if (a[now] != 0)
            {
                j++;
                if (j == m)
                {
                    out++;
                    cout << a[now];
                    if (out % 10 == 0)
                        cout << endl;
                    else if (i != n - 1)
                        cout << " ";
                    a[now] = 0;
                }
                now = (now + 1) % n;
            }
            else
            {
                now = (now + 1) % n;
            }
        }
    }
    if (out % 10 != 0)
        cout << endl;
}

int main()
{
    int a, b, c;
    char ch;
    cin >> a >> ch >> b >> ch >> c;
    josephus(a, b, c);
    return 0;
}