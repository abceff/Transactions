#include "HashTable.h"

namespace s21 {
HashTable::HashTable() {
    values_vector = new std::vector<Values *>;
    values_vector->resize(buffer_size_);
    for (auto &values : *values_vector) {
        values = nullptr;
    }
    deleted = new std::vector<bool>;
    deleted->resize(buffer_size_);
    for (auto value : *deleted) {
        value = false;
    }
}

HashTable::~HashTable() {
    for (auto &values : *values_vector) {
        delete values;
    }
    delete values_vector;
    delete deleted;
}

void HashTable::Set(Values values) {
    if (!Exists(values.key_)) {
        if (number_of_indices_filled_in_ >= (double)values_vector->size() * 0.75) {
            Rehash();
        }
        int key_int = StringToKeyInt(values.key_);
        i_ = 0;
        while (true) {
            int index = HashFunction(key_int);
            if (!(*values_vector)[index]) {
                (*deleted)[index] = false;
                (*values_vector)[index] = new Values(values);
                ++number_of_indices_filled_in_;
                if (values.ex_ > 0) {
                    std::thread thread(DeleteByTimer, this, values.key_,
                                       std::ref((*values_vector)[index]->ex_));
                    thread.detach();
                }
                break;
            } else if ((*values_vector)[index]->key_.c_str() == values.key_.c_str()) {
                break;
            }
        }
    }
}

Values HashTable::Get(std::string key) {
    int key_int = StringToKeyInt(key), number_of_scanned_keys = 0;
    i_ = 0;
    Values empty_values;
    while (true) {
        int index = HashFunction(key_int);
        if (++number_of_scanned_keys == (int)values_vector->size()) {
            return empty_values;
        } else if (!(*values_vector)[index] && !(*deleted)[index]) {
            return empty_values;
        } else if ((*values_vector)[index] && (*values_vector)[index]->key_ == key) {
            return *(*values_vector)[index];
        }
    }
}

bool HashTable::Exists(std::string key) {
    int key_int = StringToKeyInt(key), number_of_scanned_keys = 0;
    i_ = 0;
    Values empty_values;
    while (true) {
        int index = HashFunction(key_int);
        if (++number_of_scanned_keys == (int)values_vector->size()) {
            return false;
        } else if (!(*values_vector)[index] && !(*deleted)[index]) {
            return false;
        } else if ((*values_vector)[index] && (*values_vector)[index]->key_ == key) {
            return true;
        }
    }
}

bool HashTable::Del(std::string key) {
    if (number_of_deleted_indices_ >= (double)values_vector->size() * 0.25) Rehash();
    int key_int = StringToKeyInt(key), number_of_scanned_keys = 0;
    i_ = 0;
    Values empty_values;
    while (true) {
        int index = HashFunction(key_int);
        if (++number_of_scanned_keys == (int)values_vector->size()) {
            return false;
        } else if (!(*values_vector)[index] && !(*deleted)[index]) {
            return false;
        } else if ((*values_vector)[index] && (*values_vector)[index]->key_ == key) {
            delete (*values_vector)[index];
            (*values_vector)[index] = nullptr;
            (*deleted)[index] = true;
            ++number_of_deleted_indices_;
            return true;
        }
    }
}

bool HashTable::Update(Values values) {
    int key_int = StringToKeyInt(values.key_), number_of_scanned_keys = 0;
    i_ = 0;
    while (true) {
        int index = HashFunction(key_int);
        if (++number_of_scanned_keys == (int)values_vector->size()) {
            return false;
        } else if (!(*values_vector)[index] && !(*deleted)[index]) {
            return false;
        } else if ((*values_vector)[index] && (*values_vector)[index]->key_ == values.key_) {
            if (values.last_name_ != "-") (*values_vector)[index]->last_name_ = values.last_name_;
            if (values.first_name_ != "-") (*values_vector)[index]->first_name_ = values.first_name_;
            if (values.year_of_birth_ != -1) (*values_vector)[index]->year_of_birth_ = values.year_of_birth_;
            if (values.city_ != "-") (*values_vector)[index]->city_ = values.city_;
            if (values.number_of_coins_ != -1)
                (*values_vector)[index]->number_of_coins_ = values.number_of_coins_;
            return true;
        }
    }
}

std::vector<std::string> HashTable::Keys() {
    std::vector<std::string> return_vector;
    for (auto &values : *values_vector) {
        if (values) {
            return_vector.push_back(values->key_);
        }
    }
    return return_vector;
}

bool HashTable::Rename(std::string old_key, std::string new_key) {
    int key_int = StringToKeyInt(old_key), number_of_scanned_keys = 0;
    i_ = 0;
    Values empty_values;
    while (true) {
        int index = HashFunction(key_int);
        if (++number_of_scanned_keys == (int)values_vector->size()) {
            return false;
        } else if (!(*values_vector)[index] && !(*deleted)[index]) {
            return false;
        } else if ((*values_vector)[index] && (*values_vector)[index]->key_ == old_key) {
            (*values_vector)[index]->key_ = new_key;
            return true;
        }
    }
}

int HashTable::TTL(std::string key) {
    int key_int = StringToKeyInt(key), number_of_scanned_keys = 0;
    i_ = 0;
    Values empty_values;
    while (true) {
        int index = HashFunction(key_int);
        if (++number_of_scanned_keys == (int)values_vector->size()) {
            return -1;
        } else if (!(*values_vector)[index] && !(*deleted)[index]) {
            return -1;
        } else if ((*values_vector)[index] && (*values_vector)[index]->key_ == key) {
            return (*values_vector)[index]->ex_;
        }
    }
}

std::vector<std::string> HashTable::Find(Values &values) {
    std::vector<std::string> return_vector;
    for (Values *values_pointer : *values_vector) {
        if (values_pointer && (values.last_name_ == "-" || values.last_name_ == values_pointer->last_name_) &&
            (values.first_name_ == "-" || values.first_name_ == values_pointer->first_name_) &&
            (values.year_of_birth_ == -1 || values.year_of_birth_ == values_pointer->year_of_birth_) &&
            (values.city_ == "-" || values.city_ == values_pointer->city_) &&
            (values.number_of_coins_ == -1 || values.number_of_coins_ == values_pointer->number_of_coins_)) {
            return_vector.push_back(values_pointer->key_);
        }
    }
    return return_vector;
}

std::vector<Values *> HashTable::ShowAll() {
    std::vector<Values *> return_values;
    return_values.reserve(values_vector->size());
    for (auto &values : *values_vector) {
        if (values) return_values.push_back(values);
    }
    return return_values;
}

int HashTable::Export(std::fstream &fs) {
    int counter = 0;
    for (auto &values : *values_vector) {
        if (values) {
            ExportValues(values, fs, counter);
        }
    }
    return counter;
}

int HashTable::StringToKeyInt(const std::string &str) {
    int key_int = 0;
    for (char c : str) {
        key_int += c;
    }
    return key_int;
}

int HashTable::HashFunction(int key) { return (key + i_++) % values_vector->size(); }

void HashTable::Rehash() {
    int old_size = values_vector->size();

    std::vector<Values> values_for_rehashing;
    values_for_rehashing.reserve(values_vector->size());
    for (auto &values_ptr : *values_vector) {
        if (values_ptr) {
            values_for_rehashing.push_back(*values_ptr);
            delete values_ptr;
        }
    }
    delete values_vector;
    values_vector = new std::vector<Values *>;
    values_vector->resize(values_vector->size() + buffer_size_);
    for (auto &values : *values_vector) {
        values = nullptr;
    }
    number_of_indices_filled_in_ = 0;
    for (Values values : values_for_rehashing) {
        Set(values);
        ++number_of_indices_filled_in_;
    }

    delete deleted;
    deleted = new std::vector<bool>;
    deleted->resize(old_size + buffer_size_);
    for (auto value : *deleted) {
        value = false;
    }
    number_of_deleted_indices_ = 0;

    buffer_size_ *= 1.5;
}
}  // namespace s21