#include "quick_sort.hpp"

void QuickSort::sort(std::vector<int>& arr) {
    comparisons = 0;
    movements = 0;
    tempo = 0;

    if (!arr.empty()) {
        quickSort(arr, 0, arr.size() - 1);
    }
    
}

void QuickSort::quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int QuickSort::partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int tinicial = clock();

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            movements++;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    movements++;
    int tfinal = clock();
    tempo = double(tfinal - tinicial) / CLOCKS_PER_SEC;

    return (i + 1);
}
