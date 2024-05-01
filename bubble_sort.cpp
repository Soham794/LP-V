#include<iostream>
#include<stdlib.h>
#include<omp.h>

using namespace std;
void bubble(int *, int);
void swap(int &, int &);

void bubble(int *a, int n){
    for( int i = 0; i < n; i++ ){
        int first = i % 2;
        #pragma omp parallel for shared(a,first)
        for( int j = first; j < n-1; j += 2 ){
            if( a[ j ] > a[ j+1 ] ){
            swap( a[ j ], a[ j+1 ] );
            }
        }
    }
}

void swap(int &a, int &b){
    int test;
    test=a;
    a=b;
    b=test;
}


int main()
{
    int *a,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    a=new int[n];
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    
    bubble(a,n);

    cout<<"\n sorted array is=>";
    for(int i=0;i<n;i++){
        cout<<a[i]<<endl;
    }
    return 0;
}
/////////////////////////////////////

// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <omp.h>
// using namespace std;

// // Function to perform bubble sort
// void bubbleSort(std::vector<int>& arr) {
//     int n = arr.size();
//     for (int i = 0; i < n-1; i++) {
//         for (int j = 0; j < n-i-1; j++) {
//             if (arr[j] > arr[j+1]) {
//                 std::swap(arr[j], arr[j+1]);
//             }
//         }
//     }
// }
// void printVector(const std::vector<int>& arr) {
//     for (int num : arr)
//         std::cout << num << " ";
//     std::cout << std::endl;
// }

// int main() {
//     int n = 100; // Size of vector
//     std::vector<int> arr(n), arr_copy(n);
    
//     srand(42);
//     for (int i = 0; i < n; i++) {
//         arr[i] = rand() % 10000;
//         arr_copy[i] = arr[i];
//     }

//     std::cout << "Original vector:" << std::endl;
//     printVector(arr);

//     double start = omp_get_wtime();
//     bubbleSort(arr);
//     double end = omp_get_wtime();
//     std::cout << "\nSequential Bubble Sort: " << end - start << " seconds" << std::endl;
//     printVector(arr);

//     return 0;
// }