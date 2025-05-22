#include <bits/stdc++.h>

using namespace std;

map<string, int> Varible;
stack<char> Op;
stack<int> Opnum;

string Instruction;
string tmp;

int flag;

int getp(char c)
{
  switch (c)
  {
  case ('+'):
    return 3;
  case ('-'):
    return 3;
  case ('*'):
    return 5;
  case ('/'):
    return 5;
  case ('%'):
    return 5;
  case ('('):
    return 10;
  case ('^'):
    return 8;
  }
}

int GetproInstack(char c)
{
  switch (c)
  {
  case ('+'):
    return 4;
  case ('-'):
    return 4;
  case ('*'):
    return 6;
  case ('/'):
    return 6;
  case ('%'):
    return 6;
  case ('('):
    return 1;
  case ('^'):
    return 7;
  }
}

int Comput(char c, int a, int b)
{
  switch (c)
  {
  case ('+'):
    return a + b;
  case ('-'):
    return a - b;
  case ('*'):
    return a * b;
  case ('/'):
    return a / b;
  case ('%'):
    return a % b;
  case ('^'):
    return (int)pow(double(a), double(b));
  }
}

int Getvar(string tmp)
{
  int num = 0;
  flag = 0;
  int numleft = 0;
  int numright = 0;
  for (int i = 0; tmp[i]; i++)
  {
    if (tmp[i] >= '0' && tmp[i] <= '9')
    {
      if (i > 0 && tmp[i - 1] == ')')
      {
        flag = 1;
        return -1;
      }
      num = num * 10 + tmp[i] - '0';
    }

    else if (!(tmp[i] >= '0' && tmp[i] <= '9'))
    {
      if (i > 0 && tmp[i - 1] == '(' && (tmp[i] == '%' || tmp[i] == '*' || tmp[i] == '/' || tmp[i] == '^'))
      {
        flag = 1;
        return -1;
      }
      if (i > 0 && (tmp[i - 1] >= '0' && tmp[i - 1] <= '9'))
      {
        Opnum.push(num);
        num = 0;
      }
      else if (i == 0 && (tmp[i] == '+' || tmp[i] == '-') && (tmp[i + 1] >= '0' && tmp[i + 1] <= '9'))
      {
        i++;
        int k = i;
        while (tmp[k] && (tmp[k] >= '0' && tmp[k] <= '9'))
        {
          num = num * 10 + tmp[k] - '0';
          k++;
        }
        if (tmp[i - 1] == '-')
          num *= -1;
        i = k - 1;
        continue;
      }
      else if (i == 0 && (tmp[i] == '%' || tmp[i] == '*' || tmp[i] == '/' || tmp[i] == '^'))
      {
        flag = 1;
        return -1;
      }
      else if (i > 0 && !(tmp[i - 1] >= '0' && tmp[i - 1] <= '9') && (tmp[i] == '+' || tmp[i] == '-') && (tmp[i + 1] >= '0' && tmp[i + 1] <= '9'))
      {
        i++;
        int k = i;
        while (tmp[k] && (tmp[k] >= '0' && tmp[k] <= '9'))
        {
          num = num * 10 + tmp[k] - '0';
          k++;
        }
        if (tmp[i - 1] == '-')
          num *= -1;
        i = k - 1;
        continue;
      }
      if (Op.empty() || tmp[i] == '(')
      {
        if (tmp[i] == '(')
        {
          if (i > 0 && (tmp[i - 1] >= '0' && tmp[i - 1] <= '9' || tmp[i - 1] == ')'))
          {
            flag = 1;
            return -1;
          }
        }
        Op.push(tmp[i]);
        if (tmp[i] == '(')
          numleft++;
        continue;
      }
      else if (tmp[i] == ')')
      {
        numright++;
        if (numright > numleft)
        {
          flag = 1;
          return -1;
        }
        char op;
        while (!Op.empty() && (op = Op.top()) != '(')
        {
          int b = Opnum.top();
          Opnum.pop();
          int a = Opnum.top();
          Opnum.pop();
          if (b == 0 && op == '/')
          {
            flag = 2;
            return -1;
          }
          else if (b < 0 && op == '^')
          {
            flag = 1;
            return -1;
          }
          else
          {
            Opnum.push(Comput(op, a, b));
          }
          Op.pop();
        }
        Op.pop();
      }
      else
      {
        int Incoming = getp(tmp[i]);
        int Instack;
        char op;
        while (!Op.empty() && (Instack = GetproInstack(Op.top())) > Incoming)
        {
          op = Op.top();
          int b = Opnum.top();
          Opnum.pop();
          int a = Opnum.top();
          Opnum.pop();
          if (b == 0 && op == '/')
          {
            flag = 2;
            return -1;
          }
          else if (b < 0 && op == '^')
          {
            flag = 1;
            return -1;
          }
          else
          {
            Opnum.push(Comput(op, a, b));
          }
          Op.pop();
        }
        Op.push(tmp[i]);
      }
    }
  }
  if (tmp[tmp.length() - 1] >= '0' && tmp[tmp.length() - 1] <= '9')
    Opnum.push(num);
  if (!Op.empty() || !Opnum.empty())
  {

    while (!Op.empty())
    {
      char op = Op.top();
      if (op == '(')
      {
        flag = 1;
        return -1;
      }
      int b = Opnum.top();
      Opnum.pop();
      int a = Opnum.top();
      Opnum.pop();
      if (b == 0 && op == '/')
      {
        flag = 2;
        return -1;
      }
      else if (b < 0 && op == '^')
      {
        flag = 1;
        return -1;
      }
      else
      {
        Opnum.push(Comput(op, a, b));
      }
      Op.pop();
    }
    return Opnum.top();
  }
  else
    return num;
}

int main()
{
  int T;
  scanf("%d%*c", &T);
  while (T--)
  {
    while (!Op.empty())
      Op.pop();
    while (!Opnum.empty())
      Opnum.pop();
    getline(cin, Instruction);
    int ans = Getvar(Instruction);
    if (flag == 1)
      printf("error.\n");
    else if (flag == 2)
    {
      printf("Divide 0.\n");
    }
    else
    {
      printf("%d\n", ans);
    }
  }
  return 0;
}
