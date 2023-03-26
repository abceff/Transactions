#include "InvestigationOfTimeCharacteristics.h"

namespace s21 {
void InvestigationOfTimeCharacteristics::RequestNumberOfRepetitions() {
    std::cout << "Enter number of repetitions: ";
    std::cin >> number_of_repetitions_;
    if (number_of_repetitions_ < 1) {
        std::cout << "The number must be greater than 0";
        RequestNumberOfRepetitions();
    }
}

void InvestigationOfTimeCharacteristics::MeasureHashTableAverageWorkingTime() {
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < number_of_repetitions_; ++i) {
        Values values;
        values.key_ = std::string("key") + std::to_string(i);
        values.last_name_ = "aboba";
        values.first_name_ = "aboba";
        values.city_ = "aboba";
        values.year_of_birth_ = 2000;
        values.number_of_coins_ = i;
        hash_table->Set(values);
        hash_table->Get(values.key_);
        hash_table->ShowAll();
        hash_table->Find(values);
    }
    for (int i = 0; i < number_of_repetitions_; ++i) {
        hash_table->Del(std::string("key") + std::to_string(i));
    }
    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start_time;
    average_times.push_back(duration.count() / number_of_repetitions_);
}

void InvestigationOfTimeCharacteristics::MeasureSelfBalancingBinarySearchTreeAverageWorkingTime() {
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < number_of_repetitions_; ++i) {
        Values values;
        values.key_ = std::string("key") + std::to_string(i);
        values.last_name_ = "aboba";
        values.first_name_ = "aboba";
        values.city_ = "aboba";
        values.year_of_birth_ = 2000;
        values.number_of_coins_ = i;
        self_balancing_binary_search_tree->Set(values);
        self_balancing_binary_search_tree->Get(values.key_);
        self_balancing_binary_search_tree->ShowAll();
        self_balancing_binary_search_tree->Find(values);
    }
    for (int i = 0; i < number_of_repetitions_; ++i) {
        self_balancing_binary_search_tree->Del(std::string("key") + std::to_string(i));
    }
    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start_time;
    average_times.push_back(duration.count() / number_of_repetitions_);
}

void InvestigationOfTimeCharacteristics::PrintResults() {
    std::cout << "Average hash table time: " << average_times[0] << " seconds" << std::endl;
    std::cout << "Average self balancing binary search tree time: " << average_times[1] << " seconds"
              << std::endl;
}
}  // namespace s21

int main() {
    s21::InvestigationOfTimeCharacteristics investigation;
    investigation.RequestNumberOfRepetitions();
    investigation.MeasureHashTableAverageWorkingTime();
    investigation.MeasureSelfBalancingBinarySearchTreeAverageWorkingTime();
    investigation.PrintResults();
    return 0;
}