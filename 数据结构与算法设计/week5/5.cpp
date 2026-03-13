#include <iostream>
#include <queue>
#include <cstdio>
#include <cstdlib>
using namespace std;
priority_queue<int> numQueue;
int main()
{
    int numCount, index, num, total = 0, temp;
    cin >> numCount;
    for (index = 0; index < numCount; index++)
    {
        cin >> num;
        numQueue.push(-num);
    }

    for (index = 1; index < numCount; index++)
    {
        temp = numQueue.top();
        total -= numQueue.top();
        numQueue.pop();
        temp += numQueue.top();
        total -= numQueue.top();
        numQueue.pop();
        numQueue.push(temp);
    }
    cout << "WPL=" << total << endl;
    return 0;
}
