#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace std;

int counter = 0;

void calculateCount(int total, int layers)
{
    if (total < layers + 1)
    {
        counter += 0;
        return;
    }
    else if (total == layers + 1)
    {
        counter += 1;
        return;
    }
    else
    {
        total = total - layers - 1;
        counter += 1;
        int currentLayer = 1;

        if (total == 0 || currentLayer > layers)
            return;
        int requiredNodes;
        requiredNodes = pow(2, currentLayer) - 1;

        while (total - requiredNodes > 0)
        {
            counter += pow(2, currentLayer - 1);
            currentLayer++;
            total -= requiredNodes;
            requiredNodes = pow(2, currentLayer) - 1;
            if (currentLayer > layers)
                return;
        }
        if (total - requiredNodes == 0)
        {
            counter += pow(2, currentLayer - 1);
            return;
        }
        else
            calculateCount(total, currentLayer - 1);
    }
}
int main()
{
    int total, layers, testCases;
    cin >> testCases;
    while (testCases--)
    {
        cin >> total >> layers;
        counter = 0;
        calculateCount(total, layers);
        cout << counter << endl;
    }

    return 0;
}
