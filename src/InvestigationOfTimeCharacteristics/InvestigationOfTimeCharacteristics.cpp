#include "InvestigationOfTimeCharacteristics.h"

int InvestigationOfTimeCharacteristics::RequestNumberOfRepetitions() {
    std::cout << "Enter number of repetitions: ";
    int number;
    std::cin >> number;
    if (number < 1) {
        std::cout << "The number must be greater than 0";
        return RequestNumberOfRepetitions();
    }
    return number;
}

void InvestigationOfTimeCharacteristics::MeasureAverageWorkingTime() {
    for (int i = 0; i < number_of_repetitions_; ++i) {

    }
}
