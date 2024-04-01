#include <iostream>
#include "SumaPrefijos.h"
using namespace std;

int main() {
    // Se crea un vector de prueba
    vector<int> testArray = {1, 2, 3, 4, 5};

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

