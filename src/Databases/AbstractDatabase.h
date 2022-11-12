#ifndef TRANSACTIONS_ABSTRACTDATABASE_H
#define TRANSACTIONS_ABSTRACTDATABASE_H

#include <fstream>
#include <string>

struct Values {
    Values() = default;
    ~Values() = default;
    Values(const Values& other_values) { Copy(other_values); }
    Values(const Values&& other_values) { Copy(other_values); }
    void Copy(const Values& other_values) {
        key_ = other_values.key_;
        last_name_ = other_values.last_name_;
        first_name_ = other_values.first_name_;
        year_of_birth_ = other_values.year_of_birth_;
        city_ = other_values.city_;
        number_of_coins_ = other_values.number_of_coins_;
        ex_ = other_values.ex_;
    }
    std::string key_, last_name_, first_name_, city_;
    int year_of_birth_ = -1, number_of_coins_ = -1, ex_ = -1;
};

namespace s21 {
class AbstractDatabase {
public:
    virtual ~AbstractDatabase() = default;
    virtual void Set(Values values) = 0;
    virtual Values Get(std::string key) = 0;
    virtual bool Exists(std::string key) = 0;
    virtual bool Del(std::string key) = 0;   // возвращает false, если ключа нет
    virtual bool Update(Values values) = 0;  // возвращает false, если ключа нет
    virtual std::vector<std::string> Keys() = 0;
    virtual bool Rename(std::string key_old, std::string key) = 0;  // возвращает false, если ключа нет
    virtual int TTL(std::string key) = 0;
    virtual std::vector<std::string> Find(Values values) = 0;
    virtual std::vector<Values*> ShowAll() = 0;
    virtual int Upload(std::fstream& fs) = 0;  // возвращает кол-во считанных строк
    virtual int Export(std::fstream& fs) = 0;  // возвращает кол-во выгруженных строк
};
}  // namespace s21

#endif  // TRANSACTIONS_ABSTRACTDATABASE_H
