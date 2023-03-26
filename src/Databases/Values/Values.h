#ifndef A6_TRANSACTIONS_0_VALUES_H
#define A6_TRANSACTIONS_0_VALUES_H

#include <string>

namespace s21 {
struct Values {
    Values() = default;
    Values(const Values& other_values) { Copy(other_values); }
    Values(const Values&& other_values) noexcept { Copy(other_values); }
    void Copy(const Values& other_values) {
        key_ = other_values.key_;
        last_name_ = other_values.last_name_;
        first_name_ = other_values.first_name_;
        year_of_birth_ = other_values.year_of_birth_;
        city_ = other_values.city_;
        number_of_coins_ = other_values.number_of_coins_;
        ex_ = other_values.ex_;
    }
    void operator=(const Values& other_values) { Copy(other_values); }
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
