#ifndef SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

#include "sort_algorithm.hpp"

class SelectionSort : public SortAlgorithm {
public:
    void sort(std::vector<int>& arr) override;
};

#endif