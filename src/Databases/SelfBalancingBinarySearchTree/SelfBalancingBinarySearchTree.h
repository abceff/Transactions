#ifndef TRANSACTIONS_SELFBALANCINGBINARYSEARCHTREE_H
#define TRANSACTIONS_SELFBALANCINGBINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>

#include "../AbstractDatabase/AbstractDatabase.h"

namespace s21 {
class SelfBalancingBinarySearchTree : public AbstractDatabase {
public:
    ~SelfBalancingBinarySearchTree() override;
    bool Set(Values values) override;
    Values Get(std::string key) override;
    bool Exists(std::string key) override;
    bool Del(std::string key) override;   // возвращает false, если ключа нет
    bool Update(Values values) override;  // возвращает false, если ключа нет
    std::vector<std::string> Keys() override;
    bool Rename(std::string old_key, std::string new_key) override;  // возвращает false, если ключа нет
    int TTL(std::string key) override;
    std::vector<std::string> Find(Values &values) override;
    std::vector<Values *> ShowAll() override;
    int Export(std::fstream &fs) override;  // возвращает кол-во выгруженных строк

private:
    struct Node;
    Node *root_ = nullptr;

    Node *NewNode(Values &values);
    int GetHeight(Node *node);
    int GetBalanceFactor(Node *node);
    void UpdateHeight(Node *node);
    Node *RotateLeft(Node *node);
    Node *RotateRight(Node *node);
    Node *BalanceNode(Node *node);
    Node *InsertNode(Node *node, Values &values);
    Node *DeleteNode(Node *node, std::string &key, bool &node_deleted);
    Node *MinValueNode(Node *node);
    void ClearNode(Node *node);
    void FindKeysRecursively(Node *node, std::vector<std::string> &keys);
    Node *FindNodeByKey(std::string &key);
    int &GetNodeEx(std::string &key);
    void FindKeyByValuesRecursively(Node *node, Values &values, std::vector<std::string> &return_vector);
    void GetAllValuesRecursively(Node *node, std::vector<Values *> &return_vector);
    void ExportNodesRecursively(Node *node, std::fstream &fs, int &counter);

    // debug
    void PrintWholeTree(Node *node, Node *parent);
};
}  // namespace s21

#endif  // TRANSACTIONS_SELFBALANCINGBINARYSEARCHTREE_H
