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


void takeTime(int exp_x_array, vector< vector<int>> arrays){

  int* temp_array1;
  int* temp_array2;
  int* temp_array3;

  int temp_array_size;
  SumaPrefijos sp;

  long long int secuencial_time = 0;
  long long int paraleloV1_time = 0;
  long long int paraleloV2_time = 0;

  long long int avg_secuencial_time;
  long long int avg_paraleloV1_time;
  long long int avg_paraleloV2_time;

  ofstream outfile("output/results.csv");
  outfile << "size, algorithm, time\n";

  //recorre el vector de vectores que serán ordenados
  for(int k = 0; k<arrays.size(); k++){ 

    temp_array_size = arrays[k].size();

    vector<int> temp_array1;
    vector<int> temp_array2;
    vector<int> temp_array3;

    //creamos los arrays que seran ordenados
    for(int i = 0; i<temp_array_size; i++){
      temp_array1.push_back(arrays[k][i]);
      temp_array2.push_back(arrays[k][i]);
      temp_array3.push_back(arrays[k][i]);
    }


    // Para cada tamaño de arreglo se ejecutará la suma las veces definidas 
    for(int i =0;i< exp_x_array;i++){

      secuencial_time += sp.secuencialTime(temp_array1);
      paraleloV1_time += sp.paraleloV1Time(temp_array2, 4);
      paraleloV2_time += sp.paraleloV2Time(temp_array3);

    }

    avg_secuencial_time = secuencial_time/exp_x_array;
    avg_paraleloV1_time= paraleloV1_time/exp_x_array;
    avg_paraleloV2_time= paraleloV2_time/exp_x_array;

    outfile << temp_array_size << ",Suma Secuencial,"<< avg_secuencial_time << endl;
    outfile << temp_array_size << ",Paralelo V1,"<< avg_paraleloV1_time << endl;
    outfile << temp_array_size << ",Paralelo V2,"<< avg_paraleloV2_time << endl;

  }

  outfile.close(); 

}

void printArray(vector<int> array){

    cout << " Vector: " << endl;
    // Imprimir el resultado.
    for (int num : array) {
        cout << num << ' ';
    }
    cout << endl;
}



int main(){

  vector<vector<int>> arrays = readArrayDataset("datasets/random_array_dataset.txt");
  takeTime(1, arrays);
  return 0;

}


