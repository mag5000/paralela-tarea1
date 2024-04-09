#ifndef ARRAY_SUM_H
#define ARRAY_SUM_H
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;


class SumaPrefijos {
public:
    // Constructor
    SumaPrefijos();

    // Métodos solicitados
    void secuencial(vector<int>& input);                    // Secuencial
    void paraleloV1(vector<int>& input,  int thread_count); // Hilos definido por el usuario
    void paraleloV2(vector<int>& input);                    // n-1 hilos  
    
    // Métodos para tomar tiempos de ejecución de los algoritmos
    long long secuencialTime(vector<int>& input);
    long long paraleloV1Time(vector<int>& input,  int thread_count);
    long long paraleloV2Time(vector<int>& input);

    

};

#endif // ARRAY_SUM_H
