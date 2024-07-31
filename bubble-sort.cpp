#include "bubble_sort.hpp"

void BubbleSort::sort(std::vector<int>& arr) {
    size_t tam = arr.size();
    int temp;
    comparisons = 0;
    movements = 0;
    tempo = 0;

    int tinicial = clock();

    for (size_t i = 0; i < tam - 1; i++) {
        for (size_t j = 0; j < tam - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                movements++;
            }
        }
    }

    int tfinal = clock();
    tempo = double(tfinal - tinicial) / CLOCKS_PER_SEC;
}

