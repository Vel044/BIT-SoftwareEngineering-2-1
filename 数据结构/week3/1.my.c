#include <iostream>
#include <stack>
#include <string>

using namespace std;

// 判断字符是否为运算符（+、-、*、/、^）
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// 获取运算符的优先级
int getPrecedence(char c)
{
    if (c == '^')
    {
        return 3;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else if (c == '+' || c == '-')
    {
        return 1;
    }
    else
        return 0;
    // 默认情况下，返回0
}

// 将中缀表达式转换为后缀表达式
string infixToPostfix(const string &infix)
{
    stack<char> stk; // 运算符栈

    string haveFixed; // 后缀表达式

    for (char c : infix)
    {
        if (isalpha(c)) // 如果是字母，则直接添加到后缀表达式中
        {
            haveFixed += c;
        }
        else if (c == '(' || c == '^') // 如果是左括号或者'^'，则推入栈中
        {
            stk.push(c);
        }
        else if (c == ')') // 如果是右括号
        {
            // 弹出并添加栈顶的运算符到后缀表达式，直到遇到左括号
            while (!stk.empty() && stk.top() != '(')
            {
                haveFixed += stk.top();
                stk.pop();
            }
            stk.pop(); // 弹出左括号
        }
        else if (isOperator(c)) // 如果是运算符
        {
            // 与栈顶的运算符比较优先级，将高优先级的运算符弹出并添加到后缀表达式
            while (!stk.empty() && stk.top() != '(' && getPrecedence(c) <= getPrecedence(stk.top()))
            {
                haveFixed += stk.top();
                stk.pop();
            }
            stk.push(c); // 将当前运算符推入栈中
        }
    }

    // 将栈中剩余的运算符依次弹出并添加到后缀表达式
    while (!stk.empty())
    {
        haveFixed += stk.top();
        stk.pop();
    }

    return haveFixed;
}

int main()
{
    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        string infix;
        getline(cin, infix, '#'); // 读取中缀表达式，使用'#'作为分隔符
        cin.ignore();             // 清除输入缓冲区的换行符

        string haveFixed = infixToPostfix(infix); // 转换为后缀表达式
        cout << haveFixed << endl;                // 输出后缀表达式
    }
    return 0;
}
