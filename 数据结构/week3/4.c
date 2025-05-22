#include <stdio.h>
#include <stdlib.h>

typedef struct hikouki
{
    int id, occurtime;
    struct hikouki *next;
} aeroplane; // 飞机
aeroplane airplane;
typedef struct
{
    int occupytime, totaloccupytime;
} RUNWAY; // 跑道
RUNWAY runway[200];

// 1为降落，2为起飞

aeroplane *head1 = NULL, *tail1 = NULL; // 降落
void cq1()
{ // 创造队列
    aeroplane *p;
    p = (aeroplane *)malloc(sizeof(aeroplane));
    p->id = -1;
    p->occurtime = -1;
    head1 = p;
    tail1 = p; // 空结点
}
void q1(int number, int time)
{ // 进队
    aeroplane *p;
    p = (aeroplane *)malloc(sizeof(aeroplane));
    p->next = NULL;
    p->id = number;
    p->occurtime = time;
    tail1->next = p;
    tail1 = tail1->next;
}
aeroplane outq1()
{ // 出队
    aeroplane *p;
    p = head1->next;
    head1->next = p->next;
    if (head1->next == NULL)
        tail1 = head1;
    return *p;
}

aeroplane *head2 = NULL, *tail2 = NULL; // 起飞
void cq2()
{ // 创造队列
    aeroplane *p;
    p = (aeroplane *)malloc(sizeof(aeroplane));
    p->id = -1;
    p->occurtime = -1;
    head2 = p;
    tail2 = p; // 空结点
}
void q2(int number, int time)
{ // 进队
    aeroplane *p;
    p = (aeroplane *)malloc(sizeof(aeroplane));
    p->next = NULL;
    p->id = number;
    p->occurtime = time;
    tail2->next = p;
    tail2 = tail2->next;
}
aeroplane outq2()
{ // 出队
    aeroplane *p;
    p = head2->next;
    head2->next = p->next;
    if (head2->next == NULL)
        tail2 = head2;
    return *p;
}

int empty(aeroplane *p)
{
    if (p->next == NULL)
        return 0;
    else
        return 1;
}

int main()
{
    int runwaynum, tc1, tc2;
    scanf("%d%d%d", &runwaynum, &tc1, &tc2);
    int currenttime = 0;
    int num1, num2, s1 = 5001, s2 = 1, numt1 = 0, numt2 = 0; // 每分钟数量,编号,总数量
    int end = 0, allrunwayfree = 1, i;
    int wait1 = 0, wait2 = 0; // 总等待时间
    for (i = 1; i <= runwaynum; i++)
    {
        runway[i].occupytime = 0;
        runway[i].totaloccupytime = 0;
    }
    cq1();
    cq2();                                        // 初始化队列
    printf("Current Time: %4d\n", currenttime++); // 注意空格
    while (1)
    {
        if (end != 1)
        {
            scanf("%d%d", &num1, &num2);
            if (num1 < 0 && num2 < 0)
            {
                end = 1;
            }
        }

        for (i = 0; i < num1; i++)
        {
            q1(s1++, currenttime);
            numt1++;
        }
        for (i = 0; i < num2; i++)
        {
            q2(s2++, currenttime);
            numt2++;
        }
        for (int i = 1; i <= runwaynum; i++)
        {
            if (runway[i].occupytime == 0)
            { // 跑道空闲

                if (empty(head1))
                { // 如果有下降的飞机
                    airplane = outq1();
                    runway[i].occupytime = tc1;
                    printf("airplane %04d is ready to land on runway %02d\n", airplane.id, i);
                    wait1 = wait1 + currenttime - airplane.occurtime;
                    runway[i].totaloccupytime += tc1;
                }

                else if (empty(head2))
                {
                    airplane = outq2();
                    runway[i].occupytime = tc2;
                    printf("airplane %04d is ready to takeoff on runway %02d\n", airplane.id, i);
                    wait2 = wait2 + currenttime - airplane.occurtime;
                    runway[i].totaloccupytime += tc2;
                }
            }
        }

        printf("Current Time: %4d\n", currenttime++);
        allrunwayfree = 1;

        for (int i = 1; i <= runwaynum; i++)
        { // 时间流逝
            if (runway[i].occupytime != 0)
            {
                if (!(--runway[i].occupytime))
                    printf("runway %02d is free\n", i);
                else
                    allrunwayfree = 0;
            }
        }

        if (end && (!empty(head1)) && (!empty(head2)) && allrunwayfree) // 调度完成
            break;
    }
    printf("simulation finished\n");
    printf("simulation time: %4d\n", --currenttime);

    int runway_totaltime = 0;
    double average1, average2, per;

    average1 = (double)wait1 / (double)numt1;
    // printf("%d,%d\n",wait1,numt1);
    printf("average waiting time of landing: %4.1f\n", average1);

    average2 = (double)wait2 / (double)numt2;
    printf("average waiting time of takeoff: %4.1f\n", average2);

    for (i = 1; i <= runwaynum; i++)
    {
        printf("runway %02d busy time: %4d\n", i, runway[i].totaloccupytime);
        runway_totaltime += runway[i].totaloccupytime; // 加和
    }

    per = ((double)runway_totaltime) / runwaynum * 100 / currenttime; // 百分比
    printf("runway average busy time percentage: %4.1f%%\n", per);

    return 0;
}