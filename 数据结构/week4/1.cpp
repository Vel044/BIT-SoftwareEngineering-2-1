#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Triple
{
    int row;
    int col;
    int val;
};

struct SparseMatrix
{
    int rows;
    int cols;
    int nonzeros;
    vector<Triple> data;
};

// 定义一个函数来比较两个Triple
bool compareTriple(const Triple &a, const Triple &b)
{
    if (a.row != b.row)
        return a.row < b.row;
    else
        return a.col < b.col;
}

// 定义一个函数来交换两个Triple
void swapTriple(Triple &a, Triple &b)
{
    Triple temp = a;
    a = b;
    b = temp;
}

// 在sortTriple函数中使用std::sort
void sortTriple(vector<Triple> &data)
{
    std::sort(data.begin(), data.end(), compareTriple);
}
/*
// 定义一个函数来对Triple数组进行排序
void sortTriple(vector<Triple> &data)
{
    int size = data.size();
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (data[j].row > data[j + 1].row || (data[j].row == data[j + 1].row && data[j].col > data[j + 1].col))
            {
                swapTriple(data[j], data[j + 1]);
            }
        }
    }
}
*/
SparseMatrix multiply(const SparseMatrix &A, const SparseMatrix &B)
{
    if (A.cols != B.rows)
    {
        cout << "矩阵无法相乘" << endl;
        return SparseMatrix();
    }

    // 创建A和B中数据的副本，并对它们进行排序
    vector<Triple> dataA = A.data;
    vector<Triple> dataB = B.data;
    sortTriple(dataA);
    sortTriple(dataB);

    SparseMatrix C;
    C.rows = A.rows;
    C.cols = B.cols;
    C.nonzeros = 0;

    for (int i = 0; i < A.nonzeros; ++i)
    {
        for (int j = 0; j < B.nonzeros; ++j)
        {
            if (dataA[i].col == dataB[j].row)
            {
                bool found = false;
                for (int k = 0; k < C.nonzeros; ++k)
                {
                    if (C.data[k].row == dataA[i].row && C.data[k].col == dataB[j].col)
                    {
                        C.data[k].val += dataA[i].val * dataB[j].val;
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    Triple triple;
                    triple.row = dataA[i].row;
                    triple.col = dataB[j].col;
                    triple.val = dataA[i].val * dataB[j].val;
                    C.data.push_back(triple);
                    ++C.nonzeros;
                }
            }
        }
    }
    sortTriple(C.data);

    return C;
}

int main()
{
    // 读入矩阵A
    int rowsA, colsA, nonzerosA;
    cin >> rowsA >> colsA >> nonzerosA;
    SparseMatrix A;
    A.rows = rowsA;
    A.cols = colsA;
    A.nonzeros = nonzerosA;
    for (int i = 0; i < nonzerosA; i++)
    {
        Triple t;
        cin >> t.row >> t.col >> t.val;
        A.data.push_back(t);
    }

    // 读入矩阵B
    int rowsB, colsB, nonzerosB;
    cin >> rowsB >> colsB >> nonzerosB;
    SparseMatrix B;
    B.rows = rowsB;
    B.cols = colsB;
    B.nonzeros = nonzerosB;
    for (int i = 0; i < nonzerosB; i++)
    {
        Triple t;
        cin >> t.row >> t.col >> t.val;
        B.data.push_back(t);
    }

    // 计算矩阵A和矩阵B的乘积
    SparseMatrix C = multiply(A, B);


    // 对结果矩阵C进行排序
    sortTriple(C.data);

    // 输出结果
    cout << C.rows << endl
         << C.cols << endl
         << C.nonzeros << endl;
    for (const Triple &t : C.data)
    {
        cout << t.row << "," << t.col << "," << t.val << endl;
    }

    return 0;
}