#include "AbstractDatabase.h"

namespace s21 {
int AbstractDatabase::Upload(std::fstream& fs) {
    std::string str;
    char c;
    int counter = 0;
    while (getline(fs, str)) {
        Values values;
        std::string year_of_birth, number_of_coins;
        std::istringstream iss(str);
        if (!(iss >> values.key_) || !(iss >> values.last_name_) || !(iss >> values.first_name_) ||
            !(iss >> year_of_birth) || !(iss >> values.city_) || !(iss >> number_of_coins) || (iss >> c) ||
            values.last_name_.front() != '\"' || values.last_name_.back() != '\"' ||
            values.first_name_.front() != '\"' || values.first_name_.back() != '\"' ||
            values.city_.front() != '\"' || values.city_.back() != '\"' || !Utils::IsNumber(year_of_birth) ||
            !Utils::IsNumber(number_of_coins)) {
            continue;
        }
        values.year_of_birth_ = atoi(year_of_birth.c_str());
        values.number_of_coins_ = atoi(number_of_coins.c_str());
        values.last_name_.erase(values.last_name_.begin());
        values.last_name_.erase(values.last_name_.end() - 1);
        values.first_name_.erase(values.first_name_.begin());
        values.first_name_.erase(values.first_name_.end() - 1);
        values.city_.erase(values.city_.begin());
        values.city_.erase(values.city_.end() - 1);
        Set(values);
        ++counter;
    }
    return counter;
}

void AbstractDatabase::DeleteByTimer(AbstractDatabase* object, std::string key, int& ex) {
    std::mutex m;
    while (ex > 0) {
        m.lock();
        --ex;
        m.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    object->Del(key);
}

void AbstractDatabase::ExportValues(Values* values, std::fstream& fs, int& counter) {
    fs << values->key_ << " \"" << values->last_name_ << "\" \"" << values->first_name_ << "\" "
       << values->year_of_birth_ << " \"" << values->city_ << "\" " << values->number_of_coins_ << std::endl;
    ++counter;
}
}  // namespace s21