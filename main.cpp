#include <iostream>
#include <fstream>
#include "SumaPrefijos.h"
using namespace std;

vector <vector<int>> readArrayDataset(string route){

  int size = 0;
  vector<vector<int>> arrays;
  ifstream inputfile(route);

  while(inputfile>>size){
    if(size>0){
      vector<int> temp_vector(size);
      for(int i=0; i<size;i++){
        inputfile>>temp_vector[i];
      }   
      arrays.push_back(temp_vector);
      temp_vector.clear();
    }
  }
  return arrays;
}

void printArray(vector<int> array){

    cout << " Vector: " << endl;
    // Imprimir el resultado.
    for (int num : array) {
        cout << num << ' ';
    }
    cout << endl;
}

void takeTime(int exp_x_array, vector< vector<int>> arrays){

  int temp_array_size;
  int num_arrays = arrays.size();
  SumaPrefijos sp;

  long long int secuencial_time = 0;
  long long int paraleloV1_time = 0;
  long long int paraleloV2_time = 0;

  long long int avg_secuencial_time;
  long long int avg_paraleloV1_time;
  long long int avg_paraleloV2_time;

  ofstream outfile("output/results.csv");
  outfile << "Tamaño,Hilos,algoritmo,tiempo\n";

  //recorre el vector de vectores que serán ordenados
  for(int k = 0; k<num_arrays; k++){ 

    temp_array_size = arrays[k].size();
    cout << "Tamaño actual: " << temp_array_size <<endl;

    vector<int> temp_array1(temp_array_size);
    vector<int> temp_array2(temp_array_size);
    vector<int> temp_array3(temp_array_size);
    int max_threads = temp_array_size;
    if (temp_array_size > 4096) {
        max_threads = 4096;
    }

    // Para cada tamaño de arreglo se ejecutará el algoritmo variando el número de threads en base 2
    for (int n=1;n<=max_threads;n*=2){ 

        paraleloV1_time = 0;

        for(int i =0;i< exp_x_array;i++){

            //rellenamos/reseteamos el array 
            for(int j = 0; j<temp_array_size; j++){
                temp_array2[j] = arrays[k][j];
            }

            paraleloV1_time += sp.paraleloV1Time(temp_array2, n);
            
        }

        avg_paraleloV1_time = paraleloV1_time/exp_x_array;
        outfile << temp_array_size << "," << n << ",Paralelo V1,"<< avg_paraleloV1_time << endl;
    }


    paraleloV2_time = 0;
    // Si el arreglo es menor o igual a 4096 se ejecutará el algoritmo con n-1 threads 
    if(temp_array_size<=4096){
        for(int i =0;i< exp_x_array;i++){

            //rellenamos/reseteamos los arrays 
            for(int j = 0; j<temp_array_size; j++){
                temp_array3[j] = arrays[k][j];
            }

            paraleloV2_time += sp.paraleloV2Time(temp_array3);
        }
        avg_paraleloV2_time = paraleloV2_time/exp_x_array;
        outfile << temp_array_size << "," << temp_array_size-1 << ",Paralelo V2,"<< avg_paraleloV2_time << endl;
    }

    secuencial_time = 0;
    // Para cada tamaño de arreglo se ejecutarán los algoritmos secuencial 
    for(int i =0;i< exp_x_array;i++){

        //rellenamos/reseteamos los arrays 
        for(int j = 0; j<temp_array_size; j++){
            temp_array1[j] = arrays[k][j];
        }
        secuencial_time += sp.secuencialTime(temp_array1);    
    }

    avg_secuencial_time = secuencial_time/exp_x_array;
    outfile << temp_array_size << "," << 1 << ",Secuencial,"<< avg_secuencial_time << endl;
 
  }
  outfile.close(); 
}


int main(){

  vector<vector<int>> arrays = readArrayDataset("datasets/random_array_dataset.txt");
  takeTime(1, arrays);
  return 0;

}


