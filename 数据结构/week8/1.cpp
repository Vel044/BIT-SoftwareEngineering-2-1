#include<iostream>

using namespace std;
int a[1010];
int n;

void Adjust(int x, int k)
{
    int i = x;//i是这个根节点
    int j = 2 * i;//j是下面的子节点
    int up = a[i];//那么此时i的子节点其实就是2i和2i+1
    while (true)
    {
        if (j < k && a[j] < a[j + 1])
        {//如果还没到最后一个节点且后面的节点比前一个节点大，那么直接看后面的节点
            j++;//因为我们要的是当前子节点的最大值
        }

        if (a[j] > up)
        {//如果儿子大于父亲
            a[i] = a[j];//将父亲的位置让给儿子，同时将父亲与孙子比对
            i = j;//
            j = 2 * i;
        }
        else
        {//如果两个if都没走进去的话,相当于两个子节点都不符合要求
            break;
        }
    }
    a[i] = up;
}

void heapsort()
{
    for (int i = n / 2; i >= 1; i--)
    {//从一半的位置开始调整可由二叉树的性质推得
        Adjust(i, n);
    }
}

int main()
{
    //freopen("/Users/zhj/Downloads/test.txt", "r", stdin);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {//第一个数存储位置在1！！！
        cin >> a[i];
    }
    //数组是按照大根堆的方式来构建的
    for (int i = 0; i < 3; i++)
    {//一共展示三次
        heapsort();//每一次都进行下堆调整
        for (int k = 1; k <= n; k++)
        {
            cout << a[k] << " ";
        }
        cout << endl;
        a[1] = a[n];//舍弃最大值，将原最大值的地方赋上最后的那个值
        n--;//然后堆对剩下n-1个元素调整
    }
    return 0;
}
