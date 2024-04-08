#include <iostream>
#include "SumaPrefijos.h"
using namespace std;

/*
int main() {
    // Se crea un vector de prueba
    vector<int> testArray = {1, 2, 3, 4, 5, 6, 1, 1};

    // Se crea ear una instancia de SumaPrefijos
    SumaPrefijos sm;

    // Suma acumulativa
    vector<int> sumArray = sm.sumaSecuencial(testArray);

    // Imprimir el vector de sumas 
    cout << "Suma secuencial: ";
    for (int num : sumArray) {
        cout << num << " ";
    }
    cout << std::endl;

    return 0;
}
*/



int main() {
    vector<int> data = {1,2,3,4,5,6,7,8,0,0,0,0,0,0,0,0};
   // vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8};
   // vector<int> data = {4,3,5,8,2,6,3,1};

    // Se crea ear una instancia de SumaPrefijos
    SumaPrefijos sm;
    for (int num : data) {
        cout << num << ' ';
    }
    cout << endl;

    sm.algoritmo2(data, 4);


    cout << " Resultado: " << endl;
    // Imprimir el resultado.
    for (int num : data) {
        cout << num << ' ';
    }
    cout << endl;

    return 0;
}

