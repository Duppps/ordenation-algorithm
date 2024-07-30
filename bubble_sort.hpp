#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include "sort_algorithm.hpp"

class BubbleSort : public SortAlgorithm {
public:
    void sort(std::vector<int>& arr) override;
};

#endif 
