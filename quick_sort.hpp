#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <vector>
#include "sort_order.hpp"

class QuickSort {
public:
    void sort(std::vector<int>& arr);

private:
    void quickSort(std::vector<int>& arr, int low, int high);
    int partition(std::vector<int>& arr, int low, int high);
};

#endif 
