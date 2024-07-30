#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include "sort_algorithm.hpp"

class InsertionSort : public SortAlgorithm {
public:
    void sort(std::vector<int>& arr) override;
};

#endif
