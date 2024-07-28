#include "selection_sort.hpp"

void SelectionSort::sort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int target_index = i;

        for (int j = i + 1; j < n; j++) {           
            if (arr[j] < arr[target_index]) {
                target_index = j;
            }
        }

        std::swap(arr[i], arr[target_index]);
    }
}    
