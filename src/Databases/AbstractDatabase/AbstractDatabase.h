#ifndef TRANSACTIONS_ABSTRACTDATABASE_H
#define TRANSACTIONS_ABSTRACTDATABASE_H

#include <fstream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "../../Utils/Utils.h"
#include "../Values/Values.h"

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
    virtual std::vector<std::string> Find(Values& values) = 0;
    virtual std::vector<Values*> ShowAll() = 0;
    int Upload(std::fstream& fs);  // возвращает кол-во считанных строк
    virtual int Export(std::fstream& fs) = 0;  // возвращает кол-во выгруженных строк

protected:
    static void DeleteByTimer(AbstractDatabase* object, std::string key, int& ex);
    void ExportValues(Values* values, std::fstream& fs, int& counter);
};
}  // namespace s21

#endif  // TRANSACTIONS_ABSTRACTDATABASE_H
