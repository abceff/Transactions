#include "Values.h"

namespace s21 {
    Values::Values(const Values& other_values) { Copy(other_values); }
    Values::Values(const Values&& other_values) noexcept { Copy(other_values); }
    void Values::operator=(const Values& other_values) { Copy(other_values); }
    void Values::Copy(const Values& other_values) {
        key_ = other_values.key_;
        last_name_ = other_values.last_name_;
        first_name_ = other_values.first_name_;
        year_of_birth_ = other_values.year_of_birth_;
        city_ = other_values.city_;
        number_of_coins_ = other_values.number_of_coins_;
        ex_ = other_values.ex_;
    }
}
