#ifndef ARRAY_SUM_H
#define ARRAY_SUM_H

#include <vector>
#include <cmath>
#include <threads>
using namespace std;


class SumaPrefijos {
public:
    // Constructor
    SumaPrefijos();

    // Método para calcular la suma acumulativa
    vector<int> sumaSecuencial(const vector<int>& inputArray);
//    vector<int> sumaParalelo1(const vector<int>& inputArray);
//    vector<int> sumaParalelo2(const vector<int>& inputArray);

private:

};

#endif // ARRAY_SUM_H
