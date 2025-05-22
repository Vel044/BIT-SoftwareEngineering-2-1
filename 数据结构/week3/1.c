#include <iostream>
#include <stack>
#include <string>

using namespace std;

// 判断字符是否是运算符
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
    return 0;
}

// 将中缀表达式转换为后缀表达式
string infixToPostfix(const string &infix)
{
    stack<char> stk; // 用于存储运算符的栈
    string postfix;  // 存储后缀表达式的字符串

    for (char c : infix)
    {
        if (isalpha(c))
        {                 // 判断是否为字母
            postfix += c; // 将字母直接添加到后缀表达式中
        }
        else if (c == '(' || c == '^')
        { // 左括号和指数运算符直接入栈
            stk.push(c);
        }
        else if (c == ')')
        { // 遇到右括号时，将栈中的运算符出栈并添加到后缀表达式中，直到遇到左括号为止
            while (!stk.empty() && stk.top() != '(')
            {
                postfix += stk.top();
                stk.pop();
            }
            stk.pop(); // 弹出左括号
        }
        else if (isOperator(c))
        { // 如果是运算符
            while (!stk.empty() && stk.top() != '(' && getPrecedence(c) <= getPrecedence(stk.top()))
            {
                // 当栈不为空，栈顶元素不是左括号，并且当前运算符的优先级小于等于栈顶运算符的优先级时
                postfix += stk.top(); // 将栈顶运算符出栈并添加到后缀表达式中
                stk.pop();
            }
            stk.push(c); // 当前运算符入栈
        }
    }

    // 将栈中剩余的运算符全部出栈并添加到后缀表达式中
    while (!stk.empty())
    {
        postfix += stk.top();
        stk.pop();
    }

    return postfix;
}

int main()
{
    int N;
    cin >> N; // 输入要转换的中缀表达式的个数

    for (int i = 0; i < N; i++)
    {
        string infix;
        getline(cin, infix, '#');               // 以'#'作为结束符，读取中缀表达式
        cin.ignore();                           // 忽略读取中缀表达式后的换行符
        string postfix = infixToPostfix(infix); // 调用函数将中缀表达式转换为后缀表达式
        cout << postfix << endl;                // 输出后缀表达式
    }
    return 0;
}