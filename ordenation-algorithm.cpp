#include <iostream>
#include <vector>
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = { 64, 34, 25, 12, 22, 11, 90 };

    BubbleSort bubbleSort;
    InsertionSort insertionSort;
    SelectionSort selectionSort;

    std::vector<int> arr1 = arr;
    bubbleSort.sort(arr1);
    std::cout << "Bubble Sorted array: ";
    printArray(arr1);

    std::vector<int> arr2 = arr;
    insertionSort.sort(arr2);
    std::cout << "Insertion Sorted array: ";
    printArray(arr2);

    std::vector<int> arr3 = arr;
    selectionSort.sort(arr3);
    std::cout << "Selection Sorted array: ";
    printArray(arr3);

    return 0;
}
