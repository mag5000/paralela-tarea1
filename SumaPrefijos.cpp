#include "SumaPrefijos.h"
using namespace std;

SumaPrefijos::SumaPrefijos() {}

void SumaPrefijos::secuencial(vector<int>& input) {
   
    int n = input.size();
    for (int i = 1; i < n; ++i) {
        input[i]+=input[i-1];
    }

}


void SumaPrefijos::paraleloV1(vector<int>& input, int thread_count) {
       
    int n = input.size();
    vector<thread> threads;
    vector<int> partial_sums(thread_count);

    // Primera parte: sumas parciales en cada segmento.
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back([&, i] {
            int start = i * n / thread_count;
            int end = ((i + 1) * n / thread_count);

            for (int j = start + 1; j < end; ++j) {
                input[j] += input[j - 1];
            }

            partial_sums[i] = input[end - 1];  // Guardar la suma parcial.
        });
    }

    for (auto& th : threads) {
        th.join();
    }
    threads.clear();

    // Segunda parte: sumar las sumas parciales con el algoritmo V2
    paraleloV2(partial_sums); 

    // Tercera parte: actualizar el arreglo con las sumas parciales.
    for (int i = 0; i < thread_count - 1; ++i) {  // No es necesario para el último segmento.
        threads.emplace_back([&, i] {
            int start = (i + 1) * n / thread_count;  // Comenzar desde el primer elemento del siguiente segmento.
            int end = (i + 2) * n / thread_count;

            for (int j = start; j < end; ++j) {
                input[j] += partial_sums[i];
            }
        });
    }

    for (auto& th : threads) {
        th.join();
    }
    threads.clear();
}




void SumaPrefijos::paraleloV2(vector<int>& input) {
    int n = input.size();
    int thread_count = n-1;
    int hilosActivos = n-1;
    int contador = 0;
    vector<thread> threads;
    condition_variable cv;
    mutex mtx;

    // Realizar el algoritmo de Hillis-Steele en log(n) pasos.
    for (int step = 1; step < n; step *= 2) {

        hilosActivos = thread_count - step + 1;
        contador= 0;

        for (int i = step; i <= thread_count; i++ ) { 
                
            threads.emplace_back([&, i, step]() {
                int sumaLocal = input[i] + input[i - step]; // Sumar el valor del paso anterior

                unique_lock<mutex> lock(mtx);
                contador++; // Incrementar el contador de hilos que han terminado.
                if (contador == hilosActivos) {
                   cv.notify_all(); // Notificar a todos los hilos que ya pueden escribir en el vector.
                } else {
                    cv.wait(lock, [&] { return contador == hilosActivos; }); // Esperar hasta que todos los hilos hayan terminado.
                }
                input[i] = sumaLocal; // Escribir en el vector temporal después de la espera.

            });
        }
        
        for (auto& th : threads) {
            th.join();
        }
        threads.clear();
        
    }
}

// Funciones para tomar el tiempo de cada algoritmo ========================================================================
// =========================================================================================================================

// Tiempo de ejecución suma secuencial
long long SumaPrefijos::secuencialTime(vector<int>& input){

    auto start_time = chrono::steady_clock::now();
    secuencial(input);
    auto end_time = chrono::steady_clock::now();
    long long duration = chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    return duration;

}

// Tiempo de ejecución de la suma en paralelo usando un numero de hilos definido por el usuario
long long SumaPrefijos::paraleloV1Time(vector<int>& input, int thread_count){

    auto start_time = chrono::steady_clock::now();
    paraleloV1(input, thread_count);
    auto end_time = chrono::steady_clock::now();
    long long duration = chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
 //   cout << duration << "-";
    return duration;

}

//Tiempo de ejecución de la suma utilizando n-1 hilos
long long SumaPrefijos::paraleloV2Time(vector<int>& input){

    auto start_time = chrono::steady_clock::now();
    paraleloV2(input);
    auto end_time = chrono::steady_clock::now();
    long long duration = chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    return duration;

}

