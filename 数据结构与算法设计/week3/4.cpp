#include <iostream>
using namespace std;

struct Aeroplane {
    int id, occurtime;
    Aeroplane* next;
};

typedef Aeroplane* AeroplanePtr;

struct Runway {
    int occupytime, totaloccupytime;
};

const int MAX_RUNWAYS = 200;

AeroplanePtr head1 = nullptr, tail1 = nullptr; // 降落
AeroplanePtr head2 = nullptr, tail2 = nullptr; // 起飞

void cq1() { // 创造队列
    AeroplanePtr p = new Aeroplane;
    p->id = -1;
    p->occurtime = -1;
    head1 = p;
    tail1 = p; // 空结点
}

void q1(int number, int time) { // 进队
    AeroplanePtr p = new Aeroplane;
    p->next = nullptr;
    p->id = number;
    p->occurtime = time;
    tail1->next = p;
    tail1 = tail1->next;
}

Aeroplane outq1() { // 出队
    AeroplanePtr p = head1->next;
    head1->next = p->next;
    if (head1->next == nullptr)
        tail1 = head1;
    return *p;
}

void cq2() { // 创造队列
    AeroplanePtr p = new Aeroplane;
    p->id = -1;
    p->occurtime = -1;
    head2 = p;
    tail2 = p; // 空结点
}

void q2(int number, int time) { // 进队
    AeroplanePtr p = new Aeroplane;
    p->next = nullptr;
    p->id = number;
    p->occurtime = time;
    tail2->next = p;
    tail2 = tail2->next;
}

Aeroplane outq2() { // 出队
    AeroplanePtr p = head2->next;
    head2->next = p->next;
    if (head2->next == nullptr)
        tail2 = head2;
    return *p;
}

int empty(AeroplanePtr p) {
    return (p->next == nullptr) ? 0 : 1;
}

int main() {
    int runwaynum, tc1, tc2;
    cin >> runwaynum >> tc1 >> tc2;
    int currenttime = 0;
    int num1, num2, s1 = 5001, s2 = 1, numt1 = 0, numt2 = 0; // 每分钟数量,编号,总数量
    int end = 0, allrunwayfree = 1, i;
    int wait1 = 0, wait2 = 0; // 总等待时间

    Runway runway[MAX_RUNWAYS];
    for (i = 0; i < runwaynum; i++) {
        runway[i].occupytime = 0;
        runway[i].totaloccupytime = 0;
    }

    cq1();
    cq2(); // 初始化队列
    cout << "Current Time: " << currenttime++ << endl; // 注意空格

    while (1) {
        if (end != 1) {
            cin >> num1 >> num2;
            if (num1 < 0 && num2 < 0) {
                end = 1;
            }
        }

        for (i = 0; i < num1; i++) {
            q1(s1++, currenttime);
            numt1++;
        }
        for (i = 0; i < num2; i++) {
            q2(s2++, currenttime);
            numt2++;
        }
        for (int i = 0; i < runwaynum; i++) {
            if (runway[i].occupytime == 0) { // 跑道空闲
                if (empty(head1)) { // 如果有下降的飞机
                    Aeroplane airplane = outq1();
                    runway[i].occupytime = tc1;
                    cout << "airplane " << airplane.id << " is ready to land on runway " << i << endl;
                    wait1 = wait1 + currenttime - airplane.occurtime;
                    runway[i].totaloccupytime += tc1;
                } else if (empty(head2)) {
                    Aeroplane airplane = outq2();
                    runway[i].occupytime = tc2;
                    cout << "airplane " << airplane.id << " is ready to takeoff on runway " << i << endl;
                    wait2 = wait2 + currenttime - airplane.occurtime;
                    runway[i].totaloccupytime += tc2;
                }
            }
        }
        cout << "Current Time: " << currenttime++ << endl;
        allrunwayfree = 1;

        for (int i = 0; i < runwaynum; i++) { // 时间流逝
            if (runway[i].occupytime != 0) {
                if (!(--runway[i].occupytime))
                    cout << "runway " << i << " is free" << endl;
                else
                    allrunwayfree = 0;
            }
        }

        if (end && (!empty(head1)) && (!empty(head2)) && allrunwayfree) // 调度完成
            break;
    }
    cout << "simulation finished" << endl;
    cout << "simulation time: " << --currenttime << endl;

    int runway_totaltime = 0;
    double average1, average2, per;

    average1 = static_cast<double>(wait1) / static_cast<double>(numt1);
    // cout << wait1 << "," << numt1 << endl;
    cout << "average waiting time of landing: " << average1 << endl;

    average2 = static_cast<double>(wait2) / static_cast<double>(numt2);
    cout << "average waiting time of takeoff: " << average2 << endl;

    for (i = 0; i < runwaynum; i++) {
        cout << "runway " << i << " busy time: " << runway[i].totaloccupytime << endl;
        runway_totaltime += runway[i].totaloccupytime; // 加和
    }

    per = (static_cast<double>(runway_totaltime) / runwaynum) * 100 / currenttime; // 百分比
    cout << "runway average busy time percentage: " << per << "%" << endl;

    return 0;
}
