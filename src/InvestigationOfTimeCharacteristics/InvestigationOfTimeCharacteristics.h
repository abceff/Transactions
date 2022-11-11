#ifndef TRANSACTIONS_INVESTIGATIONOFTIMECHARACTERISTICS_H
#define TRANSACTIONS_INVESTIGATIONOFTIMECHARACTERISTICS_H

#include <iostream>
#include <vector>

class InvestigationOfTimeCharacteristics {
public:
    int RequestNumberOfRepetitions();
    void MeasureAverageWorkingTime();

private:
    int number_of_repetitions_;
    std::vector<double> times;
};

#endif  // TRANSACTIONS_INVESTIGATIONOFTIMECHARACTERISTICS_H
