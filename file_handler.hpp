#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include "sort_order.hpp"

class FileHandler {
    public:
        static std::vector<int> genArray(SortOrder order, int size);
};

#endif