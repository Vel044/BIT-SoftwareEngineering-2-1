#include <iostream>
using namespace std;

// 定义广义表结点
struct GNode
{
    int tag; // 0表示原子，1表示子表
    union
    {
        char data;      // 原子结点的值
        GNode *sublist; // 子表的指针
    };
    GNode *next; // 指向下一个结点
};

// 定义广义表类型
typedef GNode *GList;

GNode* CreateGList(const std::string& s, int& i) {
    if (i >= s.length()) {
        return nullptr; // 字符串结束，返回空指针
    }

    GNode* p = new GNode;
    p->next = nullptr;

    if (s[i] == '(') {
        // 遇到左括号，创建一个子表结点
        p->tag = 1;
        i++;
        p->sublist = CreateGList(s, i); // 递归创建子表
    } else if (s[i] == ')') {
        // 遇到右括号，返回空指针，终止广义表的创建
        i++;
        return nullptr;
    } else if (s[i] == ',') {
        // 遇到逗号，表示子表的结束或元素分隔
        i++;
        if (i < s.length() && s[i] == ' ') {
            i++; // 跳过可能的空格
        }
        return nullptr;
    } else {
        // 遇到原子，创建一个原子结点
        p->tag = 0;
        p->data = s[i]; // 存储原子值
        i++; // 移动到下一个字符
    }

    // 继续处理下一个节点
    if (i < s.length() && s[i] == ',') {
        i++; // 跳过逗号
        if (i < s.length() && s[i] == ' ') {
            i++; // 跳过可能的空格
        }
        p->next = CreateGList(s, i);
    }

    return p;
}

// 取表头运算
GList GetHead(GList L)
{
    if (L == NULL || L->tag == 0)
    {
        // 空表或原子，返回空指针
        return NULL;
    }
    else
    {
        // 返回子表的第一个元素
        return L->sublist;
    }
}

// 取表尾运算
GList GetTail(GList L)
{
    if (L == NULL || L->tag == 0)
    {
        // 空表或原子，返回空指针
        return NULL;
    }
    else
    {
        // 返回子表的第二个元素（即除去第一个元素后的剩余部分）
        return L->sublist->next;
    }
}

// 销毁广义表 L
void DestroyGList(GList &L)
{
    if (L != NULL)
    {
        if (L->tag == 0)
        {
            // 原子结点，直接删除
            delete L;
            L = NULL;
            cout << "free atom node" << endl;
        }
        else
        {
            // 子表结点，递归销毁子表和下一个结点
            DestroyGList(L->sublist);
            DestroyGList(L->next);
            delete L;
            L = NULL;
            cout << "free list node" << endl;
        }
    }
}

// 显示广义表 L 内容
void PrintGList(GList L)
{
    if (L == NULL)
    {
        cout << "()";
    }
    else if (L->tag == 0)
    {
        cout << L->data;
        if (L->next != NULL)
        {
            cout << ",";
            PrintGList(L->next);
        }
    }
    else
    {
        cout << "(";
        PrintGList(L->sublist);
        cout << ")";
        if (L->next != NULL)
        {
            cout << ",";
            PrintGList(L->next);
        }
    }
}

int main()
{
    string s;  // 输入的字符串
    int i = 0; // 字符串的索引
    int op;    // 操作指令

    cin >> s; // 输入字符串

    GList L = CreateGList(s, i); // 创建广义表

    cout << "generic list: ";
    PrintGList(L); // 显示广义表内容
    cout << endl;

    while (true)
    {
        cin >> op; // 输入指令

        if (op == 1)
        {
            // 取表头
            GList head = GetHead(L); // 获取表头
            DestroyGList(L);         // 销毁原表
            L = head;                // 更新当前表
            cout << "destroy tail" << endl;
            cout << "generic list: ";
            PrintGList(L); // 显示广义表内容
            cout << endl;
        }
        else if (op == 2)
        {
            // 取表尾
            GList tail = GetTail(L); // 获取表尾
            DestroyGList(L);         // 销毁原表
            L = tail;                // 更新当前表
            cout << "destroy head" << endl;
            cout << "generic list: ";
            PrintGList(L); // 显示广义表内容
            cout << endl;
        }
        else
        {
            // 无效指令，退出循环
            break;
        }
        if (L == NULL || L->tag == 0)
        {
            // 当前表是空或原子，退出循环
            break;
        }
    }

    return 0;
}
