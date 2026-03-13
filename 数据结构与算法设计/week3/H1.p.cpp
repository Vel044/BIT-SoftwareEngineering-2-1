#include <bits/stdc++.h>
using namespace std;
#define N 110
typedef struct
{
	string name; // name是变量的名字，例如abc，e等。
	int value;	 // value是变量的值。
} VRBL;
VRBL v[N];

// 若返回值大于1，表示运算符；若返回1，表示是数字；若返回0，表示既不是运算符也不是数字，也就是字母。注意，这里面是不考虑等于号的。
int valu(char c)
{
	if (c == ')')
		return 6;
	if (c == '^')
		return 5;
	if (c == '*' || c == '/' || c == '%')
		return 4;
	if (c == '+' || c == '-')
		return 3;
	if (c == '(')
		return 2;
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

// 两个数之间的计算
void cal(int *a1, int a2, char op)
{
	switch (op)
	{
	case '+':
		(*a1) = (*a1) + a2;
		break;
	case '-':
		(*a1) = (*a1) - a2;
		break;
	case '*':
		(*a1) = (*a1) * a2;
		break;
	case '/':
		(*a1) = (*a1) / a2;
		break;
	case '%':
		(*a1) = (*a1) % a2;
		break;
	case '^':
		(*a1) = pow((*a1), a2);
		break;
	}
}

int main()
{

	int valu(char);
	void cal(int *, int, char);

	string Formula;
	int n = 0; // n用来统计变量的个数
	while (cin >> Formula, Formula != "end")
	{

		// 如果是问号
		if (Formula.find('?') != -1)
		{

			cin >> Formula;
			// 遍历一次v，找到相应的变量
			int i;
			for (i = 0; i <= n; i++)
			{
				if (Formula == v[i].name)
				{
					break;
				}
			}
			cout << v[i].name << '=' << v[i].value << endl;
		}

		else
		{
			// 执行通常的赋值或计算
			int target, digit = 0; // digit用来遍历Formula，target是待赋值的变量
			string tpry;		   // tpry用来暂时存放读入的字符串内容

			// 找到待赋值的变量
			while (Formula[digit] != '=')
			{
				tpry += Formula[digit];
				digit++;
			}
			digit++;

			// 将待赋值的变量在v中进行匹配，如果已经有了就直接套用，否则就加入新的
			if (n == 0)
			{
				target = 0;
				v[0].name = tpry;
				n++;
			}
			else
			{
				int flag = 0;
				for (int i = 0; i < n; i++)
				{
					if (tpry == v[i].name)
					{
						flag = 1;
						target = i;
						break;
					}
				}
				if (flag == 0)
				{
					target = n;
					v[n].name = tpry;
					n++;
				}
			}

			// 计算等号后面的内容
			stack<int> Svalue; // Svalue用来存储值
			stack<char> Sop;   // Sop用来存储运算符

			int len = Formula.length(), start = digit, flag = 1; // flag用来标记正负数
			while (digit < len)
			{

				if (valu(Formula[digit]) == 1)
				// 数字
				{
					int cnt = 0;
					while (digit < len && valu(Formula[digit]) == 1)
					{
						cnt = cnt * 10 + Formula[digit] - '0';
						digit++;
					}
					Svalue.push(cnt * flag);
					flag = 1;
				}

				else if (valu(Formula[digit]) > 1)
				// 运算符
				{
					if (Sop.size() == 0)
					{
						if (digit == start && Formula[digit] == '-')
							flag = -1;
						else
							Sop.push(Formula[digit]);
					}
					else
					{
						// Sop不为空
						// 负数
						if (digit > start && Formula[digit] == '-' && valu(Formula[digit - 1]) > 1)
						{
							flag = -1;
						}

						// 左括号
						else if (Formula[digit] == '(')
						{
							Sop.push(Formula[digit]);
						}

						// 右括号
						else if (Formula[digit] == ')')
						{
							while (Sop.size() && Sop.top() != '(')
							{
								char c = Sop.top();
								Sop.pop();
								int a = Svalue.top();
								Svalue.pop();
								cal(&Svalue.top(), a, c);
							}
							Sop.pop();
						}

						else
						{
							// 连续乘方
							if (Sop.size() && Formula[digit] == '^' && Sop.top() == '^')
							{
								Sop.push('^');
							}
							else
							{
								if (Sop.size() && valu(Formula[digit]) <= valu(Sop.top()))
								{
									while (Sop.size() && valu(Formula[digit]) <= valu(Sop.top()))
									{
										char c = Sop.top();
										Sop.pop();
										int a = Svalue.top();
										Svalue.pop();
										cal(&Svalue.top(), a, c);
									}
									Sop.push(Formula[digit]);
								}
								else
								{
									Sop.push(Formula[digit]);
								}
							}
						}
					}
					digit++;
				}

				else if (valu(Formula[digit]) == 0)
				// 字母
				{
					// 找到完整的变量名称
					string word;
					while (digit < len && valu(Formula[digit]) == 0)
					{
						word += Formula[digit];
						digit++;
					}
					// 匹配并且取值，将其值存入栈
					for (int i = 0; i < n; i++)
					{
						if (v[i].name == word)
						{
							Svalue.push(v[i].value * flag);
							flag = 1;
							break;
						}
					}
				}
			}

			// 补刀
			while (Sop.size())
			{
				int a = Svalue.top();
				Svalue.pop();
				cal(&Svalue.top(), a, Sop.top());
				Sop.pop();
			}

			// 为目标变量赋新值
			v[target].value = Svalue.top();
		}
	}

	return 0;
}
