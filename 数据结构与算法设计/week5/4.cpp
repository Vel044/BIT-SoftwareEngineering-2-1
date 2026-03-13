#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cstring>

using namespace std;

// 按照格式打印节点
void printFormattedNode(char node[], int level[], int nodeCount)
{
    int i, j;
    for (i = 0; i < nodeCount; i++)
    {
        for (j = 0; j < level[i]; j++)
            cout << "    ";
        cout << node[i] << endl;
    }
}

int main(int argc, char *argv[])
{
    char currentChar, nodeArray[100]; // 读取字符，，储存字符
    int maxDegree = 0;                // 最大的度
    int i, j;
    int index = 0;       // 下标
    int levelArray[100]; // 和nodeArray的下标对应，值得意义是nodeArray[i]这个字符位于第几层（depth）
    int depth = -1;
    int degreeArray[100] = {0};
    int countArray[100] = {0};

    // freopen("file in.txt","r",stdin);
    currentChar = getchar(); // 读取字符

    while (currentChar != '\n')
    {
        switch (currentChar)
        {
        case '(':
            depth++;
            break;
        case ')':
            depth--;
            break;
        case ',':
            break;
        case ' ':
            break;
        default:
            nodeArray[index] = currentChar;
            levelArray[index++] = depth;
            break;
        }
        currentChar = getchar();
    }

    printFormattedNode(nodeArray, levelArray, index);

    for (i = 0; i < index - 1; i++)
    {
        for (j = i + 1; j < index; j++)
        {
            if (levelArray[j] == levelArray[i])
                break;
            if (levelArray[i] + 1 == levelArray[j])
                degreeArray[i]++;
        }
        maxDegree = maxDegree > degreeArray[i] ? maxDegree : degreeArray[i];
    }

    cout << "Degree of tree: " << maxDegree << endl;

    for (i = 0; i < index; i++)
    {
        countArray[degreeArray[i]]++;
    }

    for (i = 0; i < maxDegree + 1; i++)
    {
        cout << "Number of nodes of degree " << i << ": " << countArray[i] << endl;
    }

    return 0;
}
