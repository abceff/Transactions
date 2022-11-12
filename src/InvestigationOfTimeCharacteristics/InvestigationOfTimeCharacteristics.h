#ifndef TRANSACTIONS_INVESTIGATIONOFTIMECHARACTERISTICS_H
#define TRANSACTIONS_INVESTIGATIONOFTIMECHARACTERISTICS_H

#include <iostream>
#include <vector>

#include "../Databases/HashTable/HashTable.h"

namespace s21 {
class InvestigationOfTimeCharacteristics {
public:
    void RequestNumberOfRepetitions();
    void MeasureAverageWorkingTime();
    void PrintResults();

private:
    int number_of_repetitions_;
    std::vector<double> average_times;

    HashTable hash_table;
};
}  // namespace s21

#endif  // TRANSACTIONS_INVESTIGATIONOFTIMECHARACTERISTICS_H
