#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

void merge(vector<int>& arr, int start, int mid, int end) {
    vector<int> ans(end-start+1);
    int ind1 = start, ind2 = mid+1, ind = 0;
    
    while(ind1 <= mid && ind2 <= end){
        if(arr[ind1] < arr[ind2]) ans[ind++] = arr[ind1++];
        else ans[ind++] = arr[ind2++];
    }

    while(ind1 <= mid) ans[ind++] = arr[ind1++];

    while(ind2 <= end) ans[ind++] = arr[ind2++];

    for(int i=0,j=start; i<(end-start+1); i++, j++){
        arr[j] = ans[i];
    }

}

void merge_sort_parallel(vector<int>& arr, int start, int end) {
    if(start >= end) return;

    int mid = start + (end - start) / 2;
    #pragma omp parallel sections
    {
        #pragma omp section
        merge_sort_parallel(arr, start, mid);
        #pragma omp section
        merge_sort_parallel(arr, mid + 1, end);
    }
    merge(arr, start, mid, end);

}

void merge_sort_sequential(vector<int>& arr, int start, int end) {
    if(start >= end) return;

    int mid = start + (end - start) / 2;
    merge_sort_parallel(arr, start, mid);
    merge_sort_parallel(arr, mid + 1, end);
    
    merge(arr, start, mid, end);
}

void printVector(vector<int>& arr) {
    for (int num : arr) cout << num << " ";
    cout << endl;
}

int main() {

    int n = 1000; 
    vector<int> arr(n), arr_copy(n);

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
        arr_copy[i] = arr[i];
    }

    
    cout << "\nOriginal vector for sequential merge sort:" <<endl;
    printVector(arr);
    double start = omp_get_wtime();
    merge_sort_sequential(arr, 0, n-1);
    double end = omp_get_wtime();
    cout << "\nSequential Merge Sort: " << end - start << " seconds" <<endl;
    printVector(arr);



    cout << "\nOriginal vector for parallel merge sort:" <<endl;
    printVector(arr_copy);
    start = omp_get_wtime();
    merge_sort_parallel(arr_copy, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nParallel Merge Sort: " << end - start << " seconds" <<endl;
    printVector(arr_copy);

    return 0;
}
