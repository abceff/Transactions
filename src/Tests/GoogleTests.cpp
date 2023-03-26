#include <gtest/gtest.h>

#include "../Databases/HashTable/HashTable.h"
#include "../Databases/SelfBalancingBinarySearchTree/SelfBalancingBinarySearchTree.h"

char GenerateRandomLetter() { return 'a' + rand() % ('z' - 'a'); }

TEST(HashTable, UploadExport) {
    s21::HashTable hash_table;
    std::fstream fs1("TextFiles/data.txt"), fs2("TextFiles/data2.txt");
    EXPECT_EQ(hash_table.Upload(fs1), 50);
    EXPECT_EQ(hash_table.Keys().size(), 50);
    EXPECT_EQ(hash_table.ShowAll().size(), 50);
    EXPECT_EQ(hash_table.Export(fs2), 50);
}

TEST(HashTable, AllFunctions) {
    s21::HashTable hash_table;
    for (int i = 0; i < 50; ++i) {
        s21::Values values;
        values.key_ = "key" + std::to_string(i);
        for (int j = 0; j < 2; ++j) {
            values.last_name_ += GenerateRandomLetter();
            values.first_name_ += GenerateRandomLetter();
        }
        values.year_of_birth_ = 1950 + i;
        values.city_ = i % 3 == 0 ? "Kazan" : i % 3 == 1 ? "Moscow" : "Chelny";
        values.number_of_coins_ = i * i * i * i;
        hash_table.Set(values);
    }
    EXPECT_EQ(hash_table.ShowAll().size(), 50);
    for (int i = 0; i < 50; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values = hash_table.Get(key);
        EXPECT_EQ(values.year_of_birth_, 1950 + i);
        EXPECT_EQ(values.number_of_coins_, i * i * i * i);
        EXPECT_TRUE(hash_table.Exists(key));
    }
    for (int i = 0; i < 10; ++i) {
        std::string key;
        for (int j = 0; j < 5; ++j) {
            key += GenerateRandomLetter();
        }
        EXPECT_EQ(hash_table.Get(key).first_name_, "");
        EXPECT_EQ(hash_table.Get(key).city_, "");
        EXPECT_EQ(hash_table.Get(key).number_of_coins_, -1);
        EXPECT_FALSE(hash_table.Exists(key));
    }
    EXPECT_EQ(hash_table.Keys().size(), 50);
    for (int i = 0; i < 20; ++i) {
        std::string key = "key" + std::to_string(i);
        hash_table.Del(key);
        EXPECT_FALSE(hash_table.Exists(key));
    }
    EXPECT_EQ(hash_table.Keys().size(), 30);
    EXPECT_EQ(hash_table.ShowAll().size(), 30);
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values = hash_table.Get(key);
        EXPECT_EQ(values.year_of_birth_, 1950 + i);
        EXPECT_EQ(values.number_of_coins_, i * i * i * i);
        EXPECT_TRUE(hash_table.Exists(key));
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values;
        values.key_ = key;
        values.last_name_ = values.first_name_ = values.first_name_ = "-";
        values.city_ = "ГГГГГГГ";
        values.year_of_birth_ = -1;
        values.number_of_coins_ = 10000;
        EXPECT_TRUE(hash_table.Update(values));
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values = hash_table.Get(key);
        EXPECT_NE(values.last_name_, "-");
        EXPECT_EQ(values.city_, "ГГГГГГГ");
        EXPECT_EQ(values.number_of_coins_, 10000);
        EXPECT_TRUE(values.year_of_birth_ > 0);
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values = hash_table.Get(key);
        EXPECT_NE(values.last_name_, "-");
        EXPECT_EQ(values.city_, "ГГГГГГГ");
        EXPECT_EQ(values.number_of_coins_, 10000);
        EXPECT_TRUE(values.year_of_birth_ > 0);
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values = hash_table.Get(key);
        EXPECT_EQ(hash_table.Find(values).size(), 1);
        EXPECT_EQ(hash_table.Find(values)[0], values.key_);
    }
    s21::Values values;
    values.key_ = "test";
    values.last_name_ = "aboba";
    values.first_name_ = "aboba";
    values.year_of_birth_ = 2007;
    values.city_ = "Chelyabinsk";
    values.ex_ = 4;
    hash_table.Set(values);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_TRUE(hash_table.TTL("test") < 4);
    EXPECT_TRUE(hash_table.TTL("test") > 0);
    EXPECT_TRUE(hash_table.Exists("test"));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    EXPECT_FALSE(hash_table.Exists("test"));
}

TEST(SelfBalancingBinarySearchTree, UploadExport) {
    s21::SelfBalancingBinarySearchTree self_balancing_binary_search_tree;
    std::fstream fs1("TextFiles/data.txt"), fs2("TextFiles/data2.txt");
    EXPECT_EQ(self_balancing_binary_search_tree.Upload(fs1), 50);
    EXPECT_EQ(self_balancing_binary_search_tree.Keys().size(), 50);
    EXPECT_EQ(self_balancing_binary_search_tree.ShowAll().size(), 50);
    EXPECT_EQ(self_balancing_binary_search_tree.Export(fs2), 50);
}

TEST(SelfBalancingBinarySearchTree, AllFunctions) {
    s21::SelfBalancingBinarySearchTree self_balancing_binary_search_tree;
    for (int i = 0; i < 50; ++i) {
        s21::Values values;
        values.key_ = "key" + std::to_string(i);
        for (int j = 0; j < 2; ++j) {
            values.last_name_ += GenerateRandomLetter();
            values.first_name_ += GenerateRandomLetter();
        }
        values.year_of_birth_ = 1950 + i;
        values.city_ = i % 3 == 0 ? "Kazan" : i % 3 == 1 ? "Moscow" : "Chelny";
        values.number_of_coins_ = i * i * i * i;
        self_balancing_binary_search_tree.Set(values);
    }
    EXPECT_EQ(self_balancing_binary_search_tree.ShowAll().size(), 50);
    for (int i = 0; i < 50; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values = self_balancing_binary_search_tree.Get(key);
        EXPECT_EQ(values.year_of_birth_, 1950 + i);
        EXPECT_EQ(values.number_of_coins_, i * i * i * i);
        EXPECT_TRUE(self_balancing_binary_search_tree.Exists(key));
    }
    for (int i = 0; i < 10; ++i) {
        std::string key;
        for (int j = 0; j < 5; ++j) {
            key += GenerateRandomLetter();
        }
        EXPECT_EQ(self_balancing_binary_search_tree.Get(key).first_name_, "");
        EXPECT_EQ(self_balancing_binary_search_tree.Get(key).city_, "");
        EXPECT_EQ(self_balancing_binary_search_tree.Get(key).number_of_coins_, -1);
        EXPECT_FALSE(self_balancing_binary_search_tree.Exists(key));
    }
    EXPECT_EQ(self_balancing_binary_search_tree.Keys().size(), 50);
    for (int i = 0; i < 20; ++i) {
        std::string key = "key" + std::to_string(i);
        self_balancing_binary_search_tree.Del(key);
        EXPECT_FALSE(self_balancing_binary_search_tree.Exists(key));
    }
    EXPECT_EQ(self_balancing_binary_search_tree.Keys().size(), 30);
    EXPECT_EQ(self_balancing_binary_search_tree.ShowAll().size(), 30);
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values = self_balancing_binary_search_tree.Get(key);
        EXPECT_EQ(values.year_of_birth_, 1950 + i);
        EXPECT_EQ(values.number_of_coins_, i * i * i * i);
        EXPECT_TRUE(self_balancing_binary_search_tree.Exists(key));
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values;
        values.key_ = key;
        values.last_name_ = values.first_name_ = values.first_name_ = "-";
        values.city_ = "ГГГГГГГ";
        values.year_of_birth_ = -1;
        values.number_of_coins_ = 10000;
        EXPECT_TRUE(self_balancing_binary_search_tree.Update(values));
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values = self_balancing_binary_search_tree.Get(key);
        EXPECT_NE(values.last_name_, "-");
        EXPECT_EQ(values.city_, "ГГГГГГГ");
        EXPECT_EQ(values.number_of_coins_, 10000);
        EXPECT_TRUE(values.year_of_birth_ > 0);
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values = self_balancing_binary_search_tree.Get(key);
        EXPECT_NE(values.last_name_, "-");
        EXPECT_EQ(values.city_, "ГГГГГГГ");
        EXPECT_EQ(values.number_of_coins_, 10000);
        EXPECT_TRUE(values.year_of_birth_ > 0);
    }
    for (int i = 20; i < 30; ++i) {
        std::string key = "key" + std::to_string(i);
        s21::Values values = self_balancing_binary_search_tree.Get(key);
        EXPECT_EQ(self_balancing_binary_search_tree.Find(values).size(), 1);
        EXPECT_EQ(self_balancing_binary_search_tree.Find(values)[0], values.key_);
    }
    s21::Values values;
    values.key_ = "test";
    values.last_name_ = "aboba";
    values.first_name_ = "aboba";
    values.year_of_birth_ = 2007;
    values.city_ = "Chelyabinsk";
    values.ex_ = 4;
    self_balancing_binary_search_tree.Set(values);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_TRUE(self_balancing_binary_search_tree.TTL("test") < 4);
    EXPECT_TRUE(self_balancing_binary_search_tree.TTL("test") > 0);
    EXPECT_TRUE(self_balancing_binary_search_tree.Exists("test"));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    EXPECT_FALSE(self_balancing_binary_search_tree.Exists("test"));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}