#include "SumaPrefijos.h"
using namespace std;

SumaPrefijos::SumaPrefijos() {}

vector<int> SumaPrefijos::sumaSecuencial(const vector<int>& inputArray) {
    vector<int> sumArray;
    int sum = 0;
    for (int num : inputArray) {
        sum += num;
        sumArray.push_back(sum);
    }
    return sumArray;
}


void SumaPrefijos::hillisSteeleScan(vector<int>& input) {
    int n = input.size();
    int thread_count = n-1;
    vector<thread> threads;
    vector<int> temp(input.size(), 0); // Vector temporal para almacenar resultados intermedios

    // Realizar el algoritmo de Hillis-Steele en log(n) pasos.
    for (int step = 1; step < n; step *= 2) {
        // Lanzar hilos para realizar las sumas en paralelo.
        for (int i = 0; i < thread_count; ++i) {
            threads.emplace_back([&, i, step]() {
                int start = i * n / thread_count;
                int end = (i + 1) * n / thread_count;

                for (int j = start; j < end; ++j) {
                    temp[j] = input[j]; // Copiar el valor actual al vector temporal
                    if (j - step >= 0) {
                        temp[j] += input[j - step]; // Sumar el valor del paso anterior
                    }
                }
            });
        }

        for (auto& th : threads) {
            th.join();
        }

        input.swap(temp); // Intercambiar los vectores para la siguiente iteración

        for (int num : input) {
            cout << num << ' ';
        }
        cout << endl;

        threads.clear();
    }
}