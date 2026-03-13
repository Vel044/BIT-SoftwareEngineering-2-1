#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int median3[102], cnt = 0;
int numVector[10002];

/*此函数在表左端、右端和中间点三者取中值，交换到右端*/
int _Median3(int Left, int Right)
{
    int Middle = (Left + Right) / 2;//写成Right+(Left-Right)/2时WA了
    if (numVector[Left] > numVector[Middle])
        swap(numVector[Left], numVector[Middle]);
    if (numVector[Left] > numVector[Right])
        swap(numVector[Left], numVector[Right]);
    if (numVector[Middle] > numVector[Right])
        swap(numVector[Middle], numVector[Right]);
    swap(numVector[Middle], numVector[Right - 1]);
    median3[cnt++] = numVector[Right - 1];
    return numVector[Right - 1];
}

void InsertSort(int Left, int Right)
{
    for (int i = Left + 1; i <= Right; i++)
    {
        if (numVector[i] - numVector[i - 1] < 0)
        {
            int j = Left, tmp = numVector[i];//
            for (; numVector[j] < numVector[i]; j++);
            for (int k = i; k >= j + 1; k--)
                numVector[k] = numVector[k - 1];
            numVector[j] = tmp;//写成numVector[j]=numVector[i]就会出错  ???? .因为前面循环很明显对numVector[i]有改动啊
        }
    }
}

int Partation(int Left, int Right)
{
    if (Right - Left < 5)//元素个数不足cutoff=5使用插入排序
    {
        InsertSort(Left, Right);
        return -1;
    }
    else
    {
        int pivot = _Median3(Left, Right);
        int  R = Right - 1, L = Left;
        while (L < R)
        {
            while (L < R&&numVector[++L] < pivot);//小于或等于pivot停步
            while (L < R&&numVector[--R] > pivot);//大于或等于pivot停步
            swap(numVector[L], numVector[R]);
        }
        swap(numVector[L], numVector[Right - 1]);
        return L;
    }
}

void QuickSort(int Left, int Right)
{
    if (Left < Right)
    {
        int Middle = Partation(Left, Right);//划分
        if (Middle != -1)
        {
            QuickSort(Left, Middle - 1);//对左侧子序列快排
            QuickSort(Middle + 1, Right);//对右侧子序列快排
        }
    }
}

int main()
{
    int T = 0;
    string st;
    while(1)
    {
        cin >> st;
        if (st.at(0) == '#')
            break;
        numVector[T++] = atoi(st.c_str());
    }
    QuickSort(0, T - 1);//快排
    cout << "After Sorting:" << endl;
    for (int j = 0; j < T; j++)
        cout << numVector[j] << " ";
    cout << endl;
    cout << "Median3 Value:" << endl;
    if (T > 5)
    {
        for (int j = 0; j < cnt; j++)
            cout << median3[j] << " ";
    }
    else
        cout << "none";
    cout << endl;

    return 0;
}