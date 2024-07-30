#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include "sort_algorithm.hpp"

class ShellSort : public SortAlgorithm {
public:
    void sort(std::vector<int>& arr) override;
};

#endif 
