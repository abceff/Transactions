#include "Utils.h"

namespace s21 {
bool Utils::IsNumber(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return it == s.end();
}
}  // namespace s21
