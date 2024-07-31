#include "insertion_sort.hpp"

void InsertionSort::sort(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    comparisons = 0;
    movements = 0;
    tempo = 0;

    int tinicial = clock();    

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        comparisons++;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            movements++;

            if (j >= 0 && arr[j] > key) {
                comparisons++;
            }
        }

        arr[j + 1] = key;
        movements++;
    }

    int tfinal = clock();
    tempo = double(tfinal - tinicial) / CLOCKS_PER_SEC;
}
