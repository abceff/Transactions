#ifndef A6_TRANSACTIONS_0_VALUES_H
#define A6_TRANSACTIONS_0_VALUES_H

#include <string>

namespace s21 {
struct Values {
    Values() = default;
    Values(const Values& other_values);
    Values(const Values&& other_values) noexcept;
    void Copy(const Values& other_values);
    void operator=(const Values& other_values);
    std::string key_;
    std::string last_name_;
    std::string first_name_;
    std::string city_;
    int year_of_birth_ = -1;
    int number_of_coins_ = -1;
    int ex_ = -1;
};
}  // namespace s21

#endif  // A6_TRANSACTIONS_0_VALUES_H
