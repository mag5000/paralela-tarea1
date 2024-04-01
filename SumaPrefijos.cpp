#include "SumaPrefijos.h"
using namespace std;

SumaPrefijos::SumaPrefijos() {}

vector<int> SumaPrefijos::sumaSecuencial(const std::vector<int>& inputArray) {
    std::vector<int> sumArray;
    int sum = 0;
    for (int num : inputArray) {
        sum += num;
        sumArray.push_back(sum);
    }
    return sumArray;
}



//===================================================
//
// void prefixSum(std::vector<int>& arr, int d, int k) {
//    if (k >= pow(2, d)) {
//        arr[k] = arr[k] + arr[k - pow(2, d)];
//    }
// }

// void hillisSteele(std::vector<int>& arr) {
//    int n = arr.size();
//    int d_max = log2(n);
//    for (int d = 0; d <= d_max; d++) {
//        vector<thread> threads;
//        for (int k = 0; k < n; k++) {
//            threads.push_back(thread(prefixSum, ref(arr), d, k));
//        }
//        for (auto& t : threads) {
//            t.join();
//        }
//    }
//}


