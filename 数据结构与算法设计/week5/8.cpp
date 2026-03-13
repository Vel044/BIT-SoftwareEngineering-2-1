#include <cstdbool>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <math.h>
#include <queue>

using namespace std;

int numQueens = 0;                 // 皇后的数量
int boardSize = 0;                 // 棋盘的大小
int totalSolutions = 0;            // 找到的解决方案的数量
int *occupiedRows = NULL;          // 存储被占用的行
int *occupiedColumns = NULL;       // 存储被占用的列
int *occupiedDiagonals = NULL;     // 正斜线,左上到右下的
int *occupiedAntiDiagonals = NULL; // 反斜线，右上到左下的

/*
检查棋盘上是否有任何未被皇后控制的格子。
如果有，返回0；否则，返回1。
*/
int checkBoardControlled()
{
    int i, j;

    for (i = 1; i <= boardSize; i++)
    { // 遍历每一行

        if (occupiedRows[i] == 999)
        { // 对于没有放皇后的行
            for (j = 1; j <= boardSize; j++)
            {
                if (occupiedColumns[j] == 999)
                { // 如果列上也没有放皇后，再看有没有斜线能控制这个格子
                    if (!(occupiedAntiDiagonals[i + j] == 1 || occupiedDiagonals[boardSize + i - j + 1] == 1))
                    {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

/*
使用回溯法寻找所有可能的解决方案。
flag：当前行是否放置皇后
level：当前正在考虑的行数
num：已经放置的皇后数量
*/
void findSolutions(bool flag, int level, int num)
{
    if (level > boardSize)
    {
        if (num != numQueens)
            return;
        if (checkBoardControlled())
            totalSolutions++;
        return;
    }

    if (boardSize - level + num < numQueens)
        return;
    if (!flag)
    {
        findSolutions(false, level + 1, num);
        findSolutions(true, level + 1, num + 1);
    }
    else
    {
        for (register int i = 1; i <= boardSize; i++)
        {

            if (occupiedColumns[i] == 999 && occupiedAntiDiagonals[level + i] == 999 && occupiedDiagonals[boardSize + level - i + 1] == 999)
            {
                occupiedRows[level] = level;
                occupiedColumns[i] = i;
                occupiedAntiDiagonals[level + i] = 1;
                occupiedDiagonals[boardSize + level - i + 1] = 1;
                findSolutions(false, level + 1, num);
                findSolutions(true, level + 1, num + 1);

                occupiedRows[level] = 999;
                occupiedColumns[i] = 999;
                occupiedAntiDiagonals[level + i] = 999;
                occupiedDiagonals[boardSize + level - i + 1] = 999;
            }
        }
    }
}

int main()
{
    cin >> boardSize;
    cin >> numQueens;

    occupiedColumns = new int[boardSize + 1];
    occupiedRows = new int[boardSize + 1];
    occupiedDiagonals = new int[2 * boardSize + 1];
    occupiedAntiDiagonals = new int[2 * boardSize + 1];

    for (register int i = 0; i <= boardSize; i++)
    {
        occupiedColumns[i] = 999;
        occupiedRows[i] = 999;
    }
    for (register int i = 0; i < 2 * boardSize + 1; i++)
    {
        occupiedDiagonals[i] = 999;
        occupiedAntiDiagonals[i] = 999;
    }

    findSolutions(false, 1, 0);
    findSolutions(true, 1, 1);
    cout << totalSolutions << endl;

    return 0;
}
