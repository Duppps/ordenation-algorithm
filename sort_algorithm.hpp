#ifndef SORT_ALGORITHM_HPP
#define SORT_ALGORITHM_HPP

#include <vector>
#include "sort_order.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>

class SortAlgorithm {
protected:
    int comparisons;
    int movements;

public:
    SortAlgorithm() : comparisons(0), movements(0) {}

    virtual void sort(std::vector<int>& arr) = 0;

    void resetMetrics() {
        comparisons = 0;
        movements = 0;
    }

    int getComparisons() const {
        return comparisons;
    }

    int getMovements() const {
        return movements;
    }
};

#endif 
