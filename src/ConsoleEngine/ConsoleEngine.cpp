#include "ConsoleEngine.h"

namespace s21 {

ConsoleEngine::~ConsoleEngine() { delete abstract_database; }

void ConsoleEngine::SetHashTable() { abstract_database = new HashTable; }

void ConsoleEngine::SetSelfBalancingBinarySearchTree() {
    abstract_database = new SelfBalancingBinarySearchTree;
}

void ConsoleEngine::Start() {
    RequestDatabaseType();
    while (true) {
        std::string function, operands;
        std::cin >> function;
        getline(std::cin, operands);
        if (function == "SET") {
            Values values;
            if (ValidateValues(operands, values)) {
                abstract_database->Set(values);
            }
        } else if (function == "GET") {
            std::string key;
            if (ValidateKey(operands, key)) {
                PrintValues(abstract_database->Get(key));
            }
        } else if (function == "EXISTS") {
            std::string key;
            if (ValidateKey(operands, key)) {
                PrintBool(abstract_database->Exists(key));
            }
        } else if (function == "DEL") {
            std::string key;
            if (ValidateKey(operands, key)) {
                PrintBool(abstract_database->Del(key));
            }
        } else if (function == "UPDATE") {
            Values values;
            if (ValidateValues(operands, values)) {
                PrintOkOrFail(abstract_database->Update(values));
            }
        } else if (function == "KEYS") {
            if (ValidateEmptyOperands(operands)) {
                PrintKeys(abstract_database->Keys());
            }
        } else if (function == "RENAME") {
            std::string old_key, new_key;
            if (ValidateRename(operands, old_key, new_key)) {
                PrintOkOrFail(abstract_database->Rename(old_key, new_key));
            }
        } else if (function == "TTL") {
            std::string key;
            if (ValidateKey(operands, key)) {
                PrintIntOrNull(abstract_database->TTL(key));
            }
        } else if (function == "FIND") {
            Values values;
            if (ValidateFind(operands, values)) {
                PrintKeys(abstract_database->Find(values));
            }
        } else if (function == "SHOWALL") {
            if (ValidateEmptyOperands(operands)) {
                PrintShowAll(abstract_database->ShowAll());
            }
        } else if (function == "UPLOAD") {
            std::fstream fs;
            if (ValidateFileName(operands, fs)) {
                PrintUploadAndExportOutput(abstract_database->Upload(fs));
            }
        } else if (function == "EXPORT") {
            std::fstream fs;
            if (ValidateFileName(operands, fs)) {
                PrintUploadAndExportOutput(abstract_database->Export(fs));
            }
        } else if (function == "EXIT") {
            break;
        } else {
            std::cout << "Invalid function" << std::endl;
        }
    }
}

void ConsoleEngine::RequestDatabaseType() {
    char type = 0;
    std::cout << "Choose database type (1 or 2):" << std::endl;
    std::cout << "\t1. Hash table" << std::endl;
    std::cout << "\t2. Self balancing binary search tree" << std::endl;
    scanf("%c", &type) != 1 || (type != '1' && type != '2');
    switch (type) {
        case '1':
            SetHashTable();
            std::cout << "Hash table interface started" << std::endl;
            break;
        case '2':
            SetSelfBalancingBinarySearchTree();
            std::cout << "Self balancing binary search tree interface started" << std::endl;
            break;
        default:
            std::cout << "You have entered the wrong character, restart the application" << std::endl;
            exit(0);
    }
}

bool ConsoleEngine::ValidateValues(std::string operands, Values& values) {
    std::istringstream iss(operands);
    char c;
    std::string tmp;
    std::string year_of_birth, number_of_coins;
    if (!(iss >> values.key_) || !(iss >> values.last_name_) || !(iss >> values.first_name_) ||
        !(iss >> year_of_birth) || !(iss >> values.city_) || !(iss >> number_of_coins)) {
        std::cout << "Invalid operands" << std::endl;
    } else if (!Utils::IsNumber(year_of_birth) && year_of_birth != "-") {
        std::cout << "ERROR: unable to cast value \"" << year_of_birth << "\" to type int" << std::endl;
    } else if (!Utils::IsNumber(number_of_coins) && year_of_birth != "-") {
        std::cout << "ERROR: unable to cast value \"" << number_of_coins << "\" to type int" << std::endl;
    } else if (iss >> tmp) {
        if (tmp == "EX") {
            if (!(iss >> tmp)) {
                std::cout << "Invalid operands" << std::endl;
            } else if (!Utils::IsNumber(tmp)) {
                std::cout << "ERROR: unable to cast value \"" << tmp << "\" to type int" << std::endl;
            } else if (iss >> c) {
                std::cout << "Too many operands" << std::endl;
            } else {
                values.ex_ = atoi(tmp.c_str());
                values.year_of_birth_ = atoi(year_of_birth.c_str());
                values.number_of_coins_ = atoi(number_of_coins.c_str());
                return true;
            }
        } else {
            std::cout << "Invalid operands" << std::endl;
        }
    } else {
        values.year_of_birth_ = year_of_birth == "-" ? -1 : atoi(year_of_birth.c_str());
        values.number_of_coins_ = number_of_coins == "-" ? -1 : atoi(number_of_coins.c_str());
        return true;
    }
    return false;
}

bool ConsoleEngine::ValidateKey(std::string operands, std::string& key) {
    std::istringstream iss(operands);
    char c;
    std::string year_of_birth, number_of_coins;
    if (!(iss >> key)) {
        std::cout << "Invalid operands" << std::endl;
    } else if (iss >> c) {
        std::cout << "Too many operands" << std::endl;
    } else {
        return true;
    }
    return false;
}

bool ConsoleEngine::ValidateEmptyOperands(std::string operands) {
    std::istringstream iss(operands);
    char c;
    std::string year_of_birth, number_of_coins;
    if (iss >> c) {
        std::cout << "This function does not accept operands" << std::endl;
    } else {
        return true;
    }
    return false;
}

bool ConsoleEngine::ValidateRename(std::string operands, std::string& old_key, std::string& new_key) {
    std::istringstream iss(operands);
    char c;
    std::string year_of_birth, number_of_coins;
    if (!(iss >> old_key) || !(iss >> new_key)) {
        std::cout << "Invalid operands" << std::endl;
    } else if (iss >> c) {
        std::cout << "Too many operands" << std::endl;
    } else {
        return true;
    }
    return false;
}

bool ConsoleEngine::ValidateFind(std::string operands, Values& values) {
    std::istringstream iss(operands);
    char c;
    std::string year_of_birth, number_of_coins;
    if (!(iss >> values.last_name_) || !(iss >> values.first_name_) || !(iss >> year_of_birth) ||
        !(iss >> values.city_) || !(iss >> number_of_coins)) {
        std::cout << "Invalid operands" << std::endl;
    } else if (!Utils::IsNumber(year_of_birth) && year_of_birth != "-") {
        std::cout << "ERROR: unable to cast value \"" << year_of_birth << "\" to type int" << std::endl;
    } else if (!Utils::IsNumber(number_of_coins) && number_of_coins != "-") {
        std::cout << "ERROR: unable to cast value \"" << number_of_coins << "\" to type int" << std::endl;
    } else if (iss >> c) {
        std::cout << "Too many operands" << std::endl;
    } else {
        values.year_of_birth_ = year_of_birth == "-" ? -1 : atoi(year_of_birth.c_str());
        values.number_of_coins_ = number_of_coins == "-" ? -1 : atoi(number_of_coins.c_str());
        return true;
    }
    return false;
}

bool ConsoleEngine::ValidateFileName(std::string operands, std::fstream& fs) {
    std::istringstream iss(operands);
    std::string filename;
    char c;
    std::string year_of_birth, number_of_coins;
    if (!(iss >> filename)) {
        std::cout << "Invalid operands" << std::endl;
    } else if (iss >> c) {
        std::cout << "Too many operands" << std::endl;
    } else {
        fs = std::fstream(filename);
        if (!fs.is_open()) {
            std::cout << "Invalid file name" << std::endl;
        } else {
            return true;
        }
    }
    return false;
}

void ConsoleEngine::PrintValues(Values values) {
    if (values.last_name_.empty() || values.first_name_.empty() || values.year_of_birth_ == -1 ||
        values.city_.empty() || values.number_of_coins_ == -1) {
        std::cout << "(null)";
    } else {
        std::cout << values.last_name_ << " " << values.first_name_ << " " << values.year_of_birth_ << " "
                  << values.city_ << " " << values.number_of_coins_;
    }
    std::cout << std::endl;
}

void ConsoleEngine::PrintBool(bool exists) { std::cout << (exists ? "true" : "false") << std::endl; }

void ConsoleEngine::PrintKeys(std::vector<std::string> keys) {
    for (int i = 0; i < (int)keys.size(); ++i) {
        std::cout << i + 1 << ") " << keys[i] << std::endl;
    }
}

void ConsoleEngine::PrintOkOrFail(bool ok) { std::cout << (ok ? "OK" : "FAIL") << std::endl; }

void ConsoleEngine::PrintIntOrNull(int value) {
    std::cout << (value == -1 ? "(null)" : std::to_string(value)) << std::endl;
}
void ConsoleEngine::PrintShowAll(std::vector<Values*> vector_of_values) {
    std::cout << "№ | Last name | First name | Year of birth | City | Number of coins |" << std::endl;
    for (int i = 0; i < (int)vector_of_values.size(); ++i) {
        std::cout << i + 1 << " \"" << vector_of_values[i]->last_name_ << "\" \""
                  << vector_of_values[i]->first_name_ << "\" " << vector_of_values[i]->year_of_birth_ << " \""
                  << vector_of_values[i]->city_ << "\" " << vector_of_values[i]->number_of_coins_
                  << std::endl;
    }
}
void ConsoleEngine::PrintUploadAndExportOutput(int value) {
    std::cout << (value ? "OK" : "FAIL") << " " << value << std::endl;
}
}  // namespace s21