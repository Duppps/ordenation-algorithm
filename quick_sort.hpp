#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include "sort_algorithm.hpp"

class QuickSort : public SortAlgorithm {
public:
    void sort(std::vector<int>& arr) override;

private:
    void quickSort(std::vector<int>& arr, int low, int high);
    int partition(std::vector<int>& arr, int low, int high);
};

#endif 
