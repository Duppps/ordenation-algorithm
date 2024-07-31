#include "shell_sort.hpp"

void ShellSort::sort(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    comparisons = 0;
    movements = 0;
    tempo = 0;

    int tinicial = clock();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            comparisons++;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                movements++;
            }

            arr[j] = temp;
        }
    }

    int tfinal = clock();
    tempo = double(tfinal - tinicial) / CLOCKS_PER_SEC;
}
