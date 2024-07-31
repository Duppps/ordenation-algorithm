#ifndef SORT_ALGORITHM_HPP
#define SORT_ALGORITHM_HPP

#include <vector>
#include "sort_order.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>

class SortAlgorithm {
protected:
    long long comparisons;
    long long movements;
    int tempo;

public:
    SortAlgorithm() : comparisons(0), movements(0), tempo(0) {}

    virtual void sort(std::vector<int>& arr) = 0;

    void resetMetrics() {
        comparisons = 0;
        movements = 0;
        tempo = 0;
    }

    long long getComparisons() const {
        return comparisons;
    }

    long long getMovements() const {
        return movements;
    }

    int getTempo() const {
        return tempo;
    }
};

#endif 
