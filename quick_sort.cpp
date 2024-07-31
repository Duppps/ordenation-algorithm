#include "quick_sort.hpp"

size_t QuickSort::partition(std::vector<int>& arr, size_t low, size_t high) {
    int pivot = arr[high];
    size_t i = low - 1;

    for (size_t j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
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

    return (i + 1);
}

void QuickSort::quickSort(std::vector<int>& arr, size_t low, size_t high) {
    if (low < high) {
        size_t pi = partition(arr, low, high);

        if (pi > 0) {
            quickSort(arr, low, pi - 1);
        }
        quickSort(arr, pi + 1, high);
    }
}

void QuickSort::sort(std::vector<int>& arr) {
    comparisons = 0;
    movements = 0;
    tempo = 0;

    int tinicial = clock();
    quickSort(arr, 0, arr.size() - 1);
    int tfinal = clock();

    tempo = double(tfinal - tinicial) / CLOCKS_PER_SEC;
}
