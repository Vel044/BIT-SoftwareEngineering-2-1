#include <bits/stdc++.h>
using namespace std;
const int MAX_NUM = 200;
int *weights = NULL;
int num;
int capacity = 0;
int optimal = 0;
int backtrack_flag = 0;
int *saved_index = NULL;

int total_max(int index, int sum)
{
    while (index <= num)
    {
        sum += weights[index++];
    }
    return sum;
}

void traceback(bool flag, int index, int sum)
{
    if (backtrack_flag)
        return;
    if (index > num)
    {
        if (sum == capacity)
        {
            optimal = sum;
            backtrack_flag = 1;
        }
        else if (sum < capacity)
            ;
        optimal = max(optimal, sum);
        return;
    }

    if (flag == false)
    {
        saved_index[index] = 0;
        traceback(true, index + 1, sum);
        traceback(false, index + 1, sum);
    }
    else
    {
        saved_index[index] = weights[index];
        sum += weights[index];
        if (sum == capacity)
        {
            optimal = sum;
            backtrack_flag = 1;
            return;
        }
        if (sum > capacity)
            return;
        if (total_max(index + 1, sum) <= optimal)
            return;

        traceback(true, index + 1, sum);

        traceback(false, index + 1, sum);
    }
}

int main()
{
    int i;

    cin >> capacity;
    cin >> num;

    weights = new int[num + 1];
    saved_index = new int[num + 1];

    for (i = 1; i <= num; i++)
    {
        scanf("%d", &weights[i]);
    }

    traceback(true, 1, 0);
    traceback(false, 1, 0);
    cout << optimal << endl;

    i = 0;
    while (i <= num)
    {
        if (saved_index[i] && i)
            cout << i << " ";
        i++;
    }
    cout << endl;

    delete[] weights;
    delete[] saved_index;

    return 0;
}
