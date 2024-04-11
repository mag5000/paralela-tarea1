#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Función encargada de crear el dataset de arreglos desordenados dados los parametros establecidos en el main.
void createRandomArrayDataset(int num_arr, int arr_min_size, int arr_max_size, int arr_max_element){

	ofstream outfile("random_array_dataset.txt");
	int size;
	int element;
	srand(time(NULL));

	for (int i = arr_min_size; i <= arr_max_size; i*=2){
	  outfile << i <<endl;
	  for (int k=0; k < i; k++){

	  	for(int j = 0; j< num_arr; j ++){
	        element = rand()%arr_max_element;
	        outfile << element <<" ";
    	}  
      }
      outfile << endl;
    }

	outfile.close();
}


int main() {

	int arr_min_size = 4;
	int arr_max_size = 1000000;
	int arr_max_element = 100;
	int num_arr = 1;

	createRandomArrayDataset(num_arr, arr_min_size, arr_max_size, arr_max_element);	

	return 0;

}
