#include <stdio.h>

long long boardHeight[100002][3];
long long maxArea, boardCount;
char tempChar;

int main()
{
    while (scanf("%lld", &boardCount) && boardCount)
    {
        tempChar = getchar();
        maxArea = 0;
        for (int i = 1; i <= boardCount; i++)
        {
            scanf("%lld", &boardHeight[i][0]);
            boardHeight[i][1] = boardHeight[i][2] = 0;
        }
        for (int i = 2; i <= boardCount; i++)
        {
            if (boardHeight[i][0] > boardHeight[i - 1][0])
                boardHeight[i][1] = 0;
            else
            {
                int k = i - 1 - boardHeight[i - 1][1] - 1;
                while (k > 0 && boardHeight[k][0] >= boardHeight[i][0])
                {
                    k = k - boardHeight[k][1] - 1;
                }
                boardHeight[i][1] = i - k - 1;
            }
        }
        for (int i = boardCount - 1; i >= 1; i--)
        {
            if (boardHeight[i][0] > boardHeight[i + 1][0])
                boardHeight[i][2] = 0;
            else
            {
                int k = i + 1 + boardHeight[i + 1][2] + 1;
                while (k <= boardCount && boardHeight[k][0] >= boardHeight[i][0])
                {
                    k = k + boardHeight[k][2] + 1;
                }
                boardHeight[i][2] = k - i - 1;
            }
        }
        for (int i = 1; i <= boardCount; i++)
        {
            if ((boardHeight[i][1] + boardHeight[i][2] + 1) * boardHeight[i][0] > maxArea)
                maxArea = (boardHeight[i][1] + boardHeight[i][2] + 1) * boardHeight[i][0];
        }
        printf("%lld\n", maxArea);
    }
    return 0;
}
