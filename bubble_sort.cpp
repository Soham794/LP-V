#include<iostream>
#include<vector>
#include<stdlib.h>
#include<omp.h>

using namespace std;

void bubble_sort_parallel(vector<int> &arr, int n){
    for( int i = 0; i < n; i++ ){
        int first = i%2;
        #pragma omp parallel for shared(arr,first)
        for( int j = first; j < n-1; j += 2 ){
            if( arr[j] > arr[j+1] ){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}


void bubble_sort_sequential(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void printVector(const std::vector<int>& arr) {
    for (int num : arr) cout << num << " ";
    cout << endl;
}


int main(){

    int n = 1000; 
    vector<int> arr(n), arr_copy(n);
    
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
        arr_copy[i] = arr[i];
    }

    cout << "\nOriginal vector for sequential bubble sort:" << endl;
    printVector(arr);

    double start = omp_get_wtime();
    bubble_sort_sequential(arr);
    double end = omp_get_wtime();
    cout << "\nSequential Bubble Sort: " << end - start << " seconds" << endl;
    printVector(arr);

    cout << "\nOriginal vector for parallel bubble sort: " << endl;
    printVector(arr_copy);

    start = omp_get_wtime();
    bubble_sort_parallel(arr_copy, n);
    end = omp_get_wtime();

    cout << "\nParallel Bubble Sort:" << end-start << " seconds" << endl;
    printVector(arr_copy);

    return 0;
}


