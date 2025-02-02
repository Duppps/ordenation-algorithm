#include "file_handler.hpp"

std::vector<int> FileHandler::genArray(SortOrder order, int size) {
    std::string fileName;

    switch (order) {
        case SortOrder::Crescente:
            fileName = "numeros_ordenados.txt";
            break;
        case SortOrder::Decrescente:
            fileName = "numeros_ordem_decrescente.txt";
            break;
        case SortOrder::Random:
            fileName = "numeros_aleatorios.txt";
            break;
        default:
            return {};
    }

    std::ifstream file(fileName);
    std::vector<int> numbers;
    int number;

    while (file >> number && numbers.size() < size) {
        numbers.push_back(number);
    }

    file.close();

    return numbers;
}

