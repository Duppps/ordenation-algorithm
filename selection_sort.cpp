#include "selection_sort.hpp"

void SelectionSort::sort(std::vector<int>& arr) {
    comparisons = 0;
    movements = 0;
    int n = static_cast<int>(arr.size());

    for (int i = 0; i < n - 1; i++) {
        int target_index = i;

        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[target_index]) {
                target_index = j;
            }
        }

        if (target_index != i) {
            std::swap(arr[i], arr[target_index]);
            movements += 3; 
        }
    }
}
