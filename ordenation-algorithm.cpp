#include <iostream>
#include <vector>
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "quick_sort.hpp"
#include "shell_sort.hpp"
#include <gtk/gtk.h>
#include "gui.hpp"

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    int status = start_gtk_application(argc, argv);

    std::vector<int> arr = { 64, 34, 25, 12, 22, 11, 90 };

    BubbleSort bubbleSort;
    InsertionSort insertionSort;
    SelectionSort selectionSort;
    QuickSort quickSort;
    ShellSort shellSort;

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

    std::vector<int> arr4 = arr;
    quickSort.sort(arr4);
    std::cout << "Quick Sorted array: ";
    printArray(arr4);

    std::vector<int> arr5 = arr;
    shellSort.sort(arr5);
    std::cout << "Shell Sorted array: ";
    printArray(arr5);

    return status;
}
