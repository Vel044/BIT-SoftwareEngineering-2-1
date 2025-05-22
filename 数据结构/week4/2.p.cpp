#include <cstdio>
#include <cstring>
#include <cstdlib>

char s[1010];
int len1 = 0, len2 = -1; // len1——len2表示每次需要取的区间长度
void gethead();          // 取表头
void gettail();          // 取表尾

int main()
{
    int n = 0, m = 0;
    memset(s, 0, sizeof(s));
    scanf("%s", s);
    printf("generic list: %s\n", s);
    len2 = strlen(s) - 1;

    int ans = 0;
    while (~scanf("%d", &ans))
    {
        if (ans == 1) // 取表头
            gethead();
        else // 取表尾
            gettail();

        if (len1 == len2) // 广义表仅剩原子，停止运行
            break;
    }
    return 0;
}

void gethead()
{
    printf("destroy tail\nfree list node\ngeneric list: ");
    int temp = -1;
    int i = len1; // 每次从上一次的位置开始取
    while (s[i] != '\0')
    {
        if (s[i] == '(')
        {
            temp++;
            if (temp == 0)
                len2 = len1 = i + 1;
            i++;
            continue;
        }
        if (s[i] == ')')
        {
            temp--;
            if (temp == 0) // 第一个左括号后面的第一对括号就是表头
            {
                len2 = i;
                break;
            }
            i++;
            continue;
        }
        if (s[i] == ',' && temp == 0) // 表中第一个逗号之前的，都是表头
        {
            len2 = i - 1;
            break;
        }
        i++;
    }
    // 输出表头
    for (int j = len1; j <= len2; j++)
    {
        printf("%c", s[j]);
    }
    printf("\n");
}

void gettail()
{
    printf("free head node\nfree list node\ngeneric list: ");
    int temp = -1;
    int vis = 0;
    int i = len1;
    while (s[i] != '\0')
    {
        if (i == len2) // 空表
        {
            vis = 1;
            break;
        }
        if (s[i] == '(')
            temp++;
        if (s[i] == ')')
            temp--;
        if (s[i] == ',' && temp == 0) // 表中的第一个逗号之后的，都是表尾
        {
            s[i] = '(';
            len1 = i;
            break;
        }
        i++;
    }
    if (vis == 1) // 空表直接输出
    {
        printf("()\n");
        return;
    }
    // 输出表尾
    for (int j = len1; j <= len2; j++)
    {
        printf("%c", s[j]);
    }
    printf("\n");
}