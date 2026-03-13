#include <stdio.h>
#include <stdlib.h>

struct node
{
    char d;
    int dnum;
    int visit;
    int chain[200];
} list[200];

void bfs(int find)
{
    int after[200], afnum = 0, i, get;
    if (list[find].visit == 0)
    {
        printf("%c", list[find].d);
        list[find].visit = 1;
    }
    for (i = list[find].dnum - 1; i >= 0; i--)
    {
        get = list[find].chain[i];
        if (list[get].visit == 0)
        {
            after[afnum] = get;
            afnum++;
            printf("%c", list[get].d);
            list[get].visit = 1;
        }
    }
    for (i = 0; i < afnum; ++i)
    {
        bfs(after[i]);
    }
}

int main()
{
    char c;
    int n = 0, a, b;
    do
    {
        c = getchar();
        getchar();
        if (c != '*')
        {
            list[n].d = c;
            list[n].dnum = 0;
            list[n].visit = 0;
            n++;
        }
        else
            break;
    } while (1);
    while (1)
    {
        scanf("%d,%d", &a, &b);
        if (a == -1 && b == -1)
            break;
        else
        {
            list[a].chain[list[a].dnum] = b;
            list[a].dnum++;
            list[b].chain[list[b].dnum] = a;
            list[b].dnum++;
        }
    }
    printf("the ALGraph is\n");
    for (int i = 0; i < n; i++)
    {
        printf("%c", list[i].d);
        for (int j = list[i].dnum - 1; j >= 0; j--)
        {
            printf(" %d", list[i].chain[j]);
        }
        printf("\n");
    }
    printf("the Breadth-First-Seacrh list:");
    for (int i = 0; i < n; i++)
    {
        if (list[i].visit == 0)
        {
            bfs(i);
        }
    }
    printf("\n");
    return 0;
}