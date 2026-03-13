#include <iostream>
using namespace std;

typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node *next;
} NODE;
typedef NODE *LinkList;

void output(LinkList);
void change(int, int, NODE *);
LinkList createList(ElemType);
void inverse(LinkList);

LinkList createList(ElemType finish) // finish：数据结束标记
{
    ElemType x;
    NODE *newNode;
    LinkList first = new NODE; // 建立头结点
    first->next = NULL;
    first->data = finish;
    cin >> x; // 约定以finish结束连续输入
    while (x != finish)
    {
        newNode = new NODE; // 建立新结点
        newNode->data = x;
        newNode->next = first->next;
        first->next = newNode;
        cin >> x;
    }
    return first;
}

void output(LinkList head)
{
    cout << "List:";
    while (head->next != NULL)
    {
        cout << head->next->data << ",";
        head = head->next;
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    LinkList head;

    head = createList(-1);
    output(head);
    inverse(head);
    output(head);
    return 0;
}

void inverse(LinkList head)
{

    if (head == NULL || head->next == NULL)
    {
        return;
    }

    LinkList pre = head->next;
    LinkList cur = pre->next; // cur指向第二个结点
    pre->next = NULL;         // 第一个结点变为最后一个结点，将其next指针置为NULL

    while (cur != NULL)
    {
        LinkList next = cur->next; // 保存下一个结点的指针
        cur->next = pre;           // 当前结点的next指针指向前一个结点
        pre = cur;                 // pre指向当前结点
        cur = next;                // cur指向下一个结点
    }
    head->next = pre; // 将头结点的next指针指向原链表的最后一个结点
}
