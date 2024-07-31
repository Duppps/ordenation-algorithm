#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include "sort_algorithm.hpp"

class QuickSort : public SortAlgorithm {
public:
    void sort(std::vector<int>& arr) override;

private:
    void quickSort(std::vector<int>& arr, size_t low, size_t high);
    size_t partition(std::vector<int>& arr, size_t low, size_t high);
    size_t medianOfThree(std::vector<int>& arr, size_t low, size_t high);
};

#endif 
