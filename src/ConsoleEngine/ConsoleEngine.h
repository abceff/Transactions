#ifndef TRANSACTIONS_CONSOLEFORHASHTABLE_H
#define TRANSACTIONS_CONSOLEFORHASHTABLE_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../Databases/AbstractDatabase/AbstractDatabase.h"
#include "../Databases/HashTable/HashTable.h"
#include "../Databases/SelfBalancingBinarySearchTree/SelfBalancingBinarySearchTree.h"
#include "../Utils/Utils.h"

namespace s21 {
class ConsoleEngine {
public:
    ~ConsoleEngine();
    void Start();
    void SetHashTable();
    void SetSelfBalancingBinarySearchTree();

private:
    void RequestDatabaseType();

    bool ValidateValues(std::string operands, Values& values);
    bool ValidateKey(std::string operands, std::string& key);
    bool ValidateEmptyOperands(std::string operands);
    bool ValidateRename(std::string operands, std::string& old_key, std::string& new_key);
    bool ValidateFind(std::string operands, Values& values);
    bool ValidateFileName(std::string operands, std::fstream& fs);

    void PrintValues(Values values);
    void PrintBool(bool exists);
    void PrintKeys(std::vector<std::string> keys);
    void PrintOkOrFail(bool ok);
    void PrintIntOrNull(int value);
    void PrintShowAll(std::vector<Values*> vector_of_values);
    void PrintUploadAndExportOutput(int value);

    AbstractDatabase* abstract_database;
};
}  // namespace s21

#endif  // TRANSACTIONS_CONSOLEFORHASHTABLE_H
