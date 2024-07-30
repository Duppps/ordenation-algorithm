#include "bubble_sort.hpp"

void BubbleSort::sort(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    comparisons = 0;
    movements = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                movements += 3; 
            }
        }
    }
}
