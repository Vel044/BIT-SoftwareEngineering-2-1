#include <stdio.h>
#include <string.h>
int main()
{
    int m, i, add, sub, num;
    char ch;
    scanf("%d", &m);
    getchar();
    for (i = 0; i < m; i++)
    {
        add = sub = 0;
        num = 0;
        while ((ch = getchar()) != '\n')
        {
            if (ch == '+')
            {
                num++;
                if (num > add)
                    add = num;
            }
            else
            {
                num--;
                if (num < sub)
                    sub = num;
            }
        }
        printf("%d\n", add - sub);
    }
}