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

    // Método secuencial
    vector<int> sumaSecuencial(const vector<int>& inputArray);

    // Método con n-1 hilos  
    void hillisSteeleScan(vector<int>& input);
    void algoritmo2(vector<int>& input,  int thread_count);


    

private:

};

#endif // ARRAY_SUM_H
