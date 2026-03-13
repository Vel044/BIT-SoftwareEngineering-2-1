#include <cstdio>
#include <cstring>
#include <cstdlib>

char genericList[1010];
int startIndex = 0, endIndex = -1; // startIndex 和 endIndex 表示每次需要取的区间长度
void getHead(); // 取表头
void getTail(); // 取表尾

int main()
{
    int n = 0, m = 0;
    memset(genericList, 0, sizeof(genericList));
    scanf("%s", genericList);
    printf("generic list: %s\n",genericList);
    endIndex = strlen(genericList) - 1;

    int ans = 0;
    while (~scanf("%d", &ans))
    {
        if (ans == 1) // 取表头
            getHead();
        else // 取表尾
            getTail();

        if (startIndex == endIndex) // 广义表仅剩原子，停止运行
            break;
    }
    return 0;
}

void getHead()
{
    printf("destroy tail\nfree list node\ngeneric list: ");
    int temp = -1;
    int i = startIndex; // 每次从上一次的位置开始取
    while (genericList[i] != '\0')
    {
        if (genericList[i] == '(')
        {
            temp++;
            if (temp == 0)
                endIndex = startIndex = i + 1;
            i++;
            continue;
        }
        if (genericList[i] == ')')
        {
            temp--;
            if (temp == 0) // 第一个左括号后面的第一对括号就是表头
            {
                endIndex = i;
                break;
            }
            i++;
            continue;
        }
        if (genericList[i] == ',' && temp == 0) // 表中第一个逗号之前的，都是表头
        {
            endIndex = i - 1;
            break;
        }
        i++;
    }
    // 输出表头
    for (int j = startIndex; j <= endIndex; j++)
    {
        printf("%c", genericList[j]);
    }
    printf("\n");
}

void getTail()
{
    printf("free head node\nfree list node\ngeneric list: ");
    int temp = -1;
    int isEmptyList = 0;
    int i = startIndex;
    while (genericList[i] != '\0')
    {
        if (i == endIndex) // 空表
        {
            isEmptyList = 1;
            break;
        }
        if (genericList[i] == '(')
            temp++;
        if (genericList[i] == ')')
            temp--;
        if (genericList[i] == ',' && temp == 0) // 表中的第一个逗号之后的，都是表尾
        {
            genericList[i] = '(';
            startIndex = i;
            break;
        }
        i++;
    }
    if (isEmptyList == 1) // 空表直接输出
    {
        printf("()\n");
        return;
    }
    // 输出表尾
    for (int j = startIndex; j <= endIndex; j++)
    {
        printf("%c", genericList[j]);
    }
    printf("\n");
}
