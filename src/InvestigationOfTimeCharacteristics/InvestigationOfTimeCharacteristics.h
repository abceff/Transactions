#ifndef TRANSACTIONS_INVESTIGATIONOFTIMECHARACTERISTICS_H
#define TRANSACTIONS_INVESTIGATIONOFTIMECHARACTERISTICS_H

#include <iostream>
#include <vector>

#include "../Databases/HashTable/HashTable.h"
#include "../Databases/SelfBalancingBinarySearchTree/SelfBalancingBinarySearchTree.h"

namespace s21 {
class InvestigationOfTimeCharacteristics {
public:
    void RequestNumberOfRepetitions();
    void MeasureHashTableAverageWorkingTime();
    void MeasureSelfBalancingBinarySearchTreeAverageWorkingTime();
    void PrintResults();

private:
    int number_of_repetitions_;
    std::vector<double> average_times;

    HashTable* hash_table = new HashTable();
    SelfBalancingBinarySearchTree* self_balancing_binary_search_tree = new SelfBalancingBinarySearchTree();
};
}  // namespace s21

#endif  // TRANSACTIONS_INVESTIGATIONOFTIMECHARACTERISTICS_H
