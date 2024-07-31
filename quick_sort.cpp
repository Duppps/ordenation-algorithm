#include "quick_sort.hpp"

void QuickSort::sort(std::vector<int>& arr) {
    comparisons = 0;
    movements = 0;
    tempo = 0;

    int tinicial = clock(); 
    quickSort(arr, 0, arr.size() - 1);
    int tfinal = clock(); 

    tempo = double(tfinal - tinicial) / CLOCKS_PER_SEC; 
}

void QuickSort::quickSort(std::vector<int>& arr, size_t low, size_t high) {
    if (low < high) {
        size_t pivot = medianOfThree(arr, low, high);
        size_t pivotIndex = partition(arr, low, high, pivot);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

size_t QuickSort::partition(std::vector<int>& arr, size_t low, size_t high, size_t pivot) {
    size_t i = low - 1;

    for (size_t j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            size_t temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            movements++;
        }
    }
    size_t temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    movements++;

    return (i + 1);
}

size_t QuickSort::medianOfThree(std::vector<int>& arr, size_t low, size_t high) {
    size_t mid = low + (high - low) / 2;

    size_t a = arr[low];
    size_t b = arr[mid];
    size_t c = arr[high];

    if ((a < b && b < c) || (c < b && b < a))
        return mid;
    if ((b < a && a < c) || (c < a && a < b))
        return low;
    return high;
}