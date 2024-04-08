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
        
        for (int num : input) {
            cout << num << ' ';
        }
        cout << endl;

        threads.clear();
    }
}


void SumaPrefijos::algoritmo2(vector<int>& input, int thread_count) {
    int n = input.size();
    vector<thread> threads;


    // Lanzar hilos para realizar las sumas en paralelo.
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back([&, i]() {

            int start = i * n / thread_count;
            int end = ((i + 1) * n / thread_count);

            cout << "inicio: " << start << "  -  fin: " << end << endl;  

            for (int j = start+1; j < end; ++j) {
                    
                input[j] += input[j - 1]; // Sumar el valor del paso anterior 
                
            }

        });
    }

    for (auto& th : threads) {
        th.join();
    }
    threads.clear();


    // Lanzar hilos para realizar las sumas en paralelo de los valores parciales.
    for (int step = (n/thread_count); step < n; step *= 2) {
        
        for (int i = 0; i < n/step; ++i) {

            threads.emplace_back([&, i, step]() {
       
//                cout << "inicio: " << start << "  -  fin: " << end << endl;  
                int posic1 =  ( step - 1 ) * i
                int posic2 =  ( ( step - 1 ) * i ) + step
                                    
                input[posic2] += input[posic1]; // Sumar el valor del paso anterior              
    

            });
        }

        for (auto& th : threads) {
            th.join();
        }
        threads.clear();

    }










    //Se imprimen los resultados
    for (int num : input) {  
        cout << num << ' ';
    }
    cout << endl;  
    
}










/*

void SumaPrefijos::Algoritmov2(vector<int>& input) {
    int n = input.size();
    int thread_count = n-1;
    vector<thread> threads;

    // Realizar el algoritmo de Hillis-Steele en log(n) pasos.
    for (int step = 1; step < n; step *= 2) {

        // Lanzar hilos para realizar las sumas en paralelo.
        for (int i = 0; i < thread_count; ++i) {
            threads.emplace_back([&, i, step]() {

                int start = i * n / thread_count;
                int end = ((i + 1) * n / thread_count)-1;

                for (int j = start+1; j < end; ++j) {
                    
                    input[j] += input[j - step]; // Sumar el valor del paso anterior 
                
                }

            });
        }

        for (auto& th : threads) {
            th.join();
        }

        for (int num : input) {  
            cout << num << ' ';
        }
        cout << endl;

        threads.clear();
    }
}


void SumaPrefijos::hillisSteeleScan(vector<int>& input) {
    int n = input.size();
    int thread_count = n-1;
    vector<thread> threads;
    vector<int> temp(input.size(), 0); // Vector temporal para almacenar resultados intermedios


    // Realizar el algoritmo de Hillis-Steele en log(n) pasos.
    for (int step = 1; step < n; step *= 2) {

    //    if (step == 1) {
    //        temp[0] = input[0]; // Copiar el primer valor 
    //    }

             
        for (int i = step; i <= thread_count; i++ ) { 
             
            threads.emplace_back([&, i, step]() {

                if (i == step) {
                    temp[i-1] = input[i-1]; // Copiar el valor actual al vector temporal    
                }

             //   if (i - step <= 0) {
             //       temp[i-1] = input[i-1]; // Copiar el valor actual al vector temporal    
             //   }
              
                temp[i] = input[i] + input[i - step]; // Sumar el valor del paso anterior    
                                    
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






*/