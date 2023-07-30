#include "SelfBalancingBinarySearchTree.h"

namespace s21 {
struct SelfBalancingBinarySearchTree::Node {
    Node(const Values &values) { values_ = values; }

    Node *left = nullptr;
    Node *right = nullptr;
    int height = 1;
    Values values_;
};

SelfBalancingBinarySearchTree::~SelfBalancingBinarySearchTree() { ClearNode(root_); }

void SelfBalancingBinarySearchTree::ClearNode(Node *node) {
    if (node) {
        if (node->left) {
            ClearNode(node->left);
        }
        if (node->right) {
            ClearNode(node->right);
        }
        delete node;
    }
}

bool SelfBalancingBinarySearchTree::Set(Values values) {
    if (!Exists(values.key_)) {
        if (!root_) {
            root_ = new Node(values);
        } else {
            InsertNode(root_, values);
        }
        if (values.ex_ > 0) {
            std::thread thread(DeleteByTimer, this, values.key_, std::ref(GetNodeEx(values.key_)));
            thread.detach();
        }
        return true;
    }
    return false;
}

Values SelfBalancingBinarySearchTree::Get(std::string key) {
    Values empty_values;
    if (!root_) {
        return empty_values;
    }
    Node *tmp = root_;
    while (true) {
        if (key == tmp->values_.key_) {
            return tmp->values_;
        }
        if (key < tmp->values_.key_ && tmp->left) {
            tmp = tmp->left;
        } else if (tmp->right) {
            tmp = tmp->right;
        } else {
            return empty_values;
        }
    }
}

bool SelfBalancingBinarySearchTree::Exists(std::string key) { return FindNodeByKey(key); }

bool SelfBalancingBinarySearchTree::Del(std::string key) {
    bool node_deleted = false;
    DeleteNode(root_, key, node_deleted);
    return node_deleted;
}

bool SelfBalancingBinarySearchTree::Update(Values values) {
    Values empty_values;
    if (!root_) {
        return false;
    }
    Node *tmp = root_;
    while (true) {
        if (values.key_ == tmp->values_.key_) {
            if (values.last_name_ != "-") tmp->values_.last_name_ = values.last_name_;
            if (values.first_name_ != "-") tmp->values_.first_name_ = values.first_name_;
            if (values.year_of_birth_ != -1) tmp->values_.year_of_birth_ = values.year_of_birth_;
            if (values.city_ != "-") tmp->values_.city_ = values.city_;
            if (values.number_of_coins_ != -1) tmp->values_.number_of_coins_ = values.number_of_coins_;
            return true;
        }
        if (values.key_ < tmp->values_.key_ && tmp->left) {
            tmp = tmp->left;
        } else if (tmp->right) {
            tmp = tmp->right;
        } else {
            return false;
        }
    }
}

std::vector<std::string> SelfBalancingBinarySearchTree::Keys() {
    std::vector<std::string> keys;
    FindKeysRecursively(root_, keys);
    return keys;
}

bool SelfBalancingBinarySearchTree::Rename(std::string old_key, std::string new_key) {
    Node *node = FindNodeByKey(old_key);
    if (node) {
        node->values_.key_ = new_key;
        return true;
    }
    return false;
}

int SelfBalancingBinarySearchTree::TTL(std::string key) {
    Node *node = FindNodeByKey(key);
    return node ? node->values_.ex_ : -1;
}

std::vector<std::string> SelfBalancingBinarySearchTree::Find(Values &values) {
    std::vector<std::string> return_vector;
    FindKeyByValuesRecursively(root_, values, return_vector);
    return return_vector;
}

std::vector<Values *> SelfBalancingBinarySearchTree::ShowAll() {
    std::vector<Values *> return_values;
    GetAllValuesRecursively(root_, return_values);
    return return_values;
}

int SelfBalancingBinarySearchTree::Export(std::fstream &fs) {
    int counter = 0;
    ExportNodesRecursively(root_, fs, counter);
    return counter;
}

SelfBalancingBinarySearchTree::Node *SelfBalancingBinarySearchTree::NewNode(Values &values) {
    return new Node(values);
}

int SelfBalancingBinarySearchTree::GetHeight(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int SelfBalancingBinarySearchTree::GetBalanceFactor(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return GetHeight(node->left) - GetHeight(node->right);
}

void SelfBalancingBinarySearchTree::UpdateHeight(Node *node) {
    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

SelfBalancingBinarySearchTree::Node *SelfBalancingBinarySearchTree::RotateLeft(Node *node) {
    Node *rightChild = node->right;
    Node *leftGrandChild = rightChild->left;
    rightChild->left = node;
    node->right = leftGrandChild;
    UpdateHeight(node);
    UpdateHeight(rightChild);
    if (node == root_) {
        root_ = rightChild;
    }
    return rightChild;
}

SelfBalancingBinarySearchTree::Node *SelfBalancingBinarySearchTree::RotateRight(Node *node) {
    Node *leftChild = node->left;
    Node *rightGrandChild = leftChild->right;
    leftChild->right = node;
    node->left = rightGrandChild;
    UpdateHeight(node);
    UpdateHeight(leftChild);
    if (node == root_) {
        root_ = leftChild;
    }
    return leftChild;
}

SelfBalancingBinarySearchTree::Node *SelfBalancingBinarySearchTree::BalanceNode(Node *node) {
    UpdateHeight(node);
    int balanceFactor = GetBalanceFactor(node);
    if (balanceFactor > 1) {
        if (GetBalanceFactor(node->left) < 0) {
            node->left = RotateLeft(node->left);
        }
        return RotateRight(node);
    } else if (balanceFactor < -1) {
        if (GetBalanceFactor(node->right) > 0) {
            node->right = RotateRight(node->right);
        }
        return RotateLeft(node);
    }
    return node;
}

SelfBalancingBinarySearchTree::Node *SelfBalancingBinarySearchTree::InsertNode(Node *node, Values &values) {
    if (!node) return NewNode(values);
    if (values.key_ < node->values_.key_) {
        node->left = InsertNode(node->left, values);
    } else if (values.key_ > node->values_.key_) {
        node->right = InsertNode(node->right, values);
    }
    return BalanceNode(node);
}

SelfBalancingBinarySearchTree::Node *SelfBalancingBinarySearchTree::DeleteNode(Node *node, std::string &key,
                                                                               bool &node_deleted) {
    if (!node) return node;

    if (key < node->values_.key_) {
        node->left = DeleteNode(node->left, key, node_deleted);
    } else if (key > node->values_.key_) {
        node->right = DeleteNode(node->right, key, node_deleted);
    } else {
        if (!node->left || !node->right) {
            Node *tmp = node->left ? node->left : node->right;

            if (!tmp) {
                tmp = node;
                node = nullptr;
            } else {
                *node = *tmp;
            }
            delete tmp;
            node_deleted = true;
        } else {
            Node *tmp = MinValueNode(node->right);

            node->values_.key_ = tmp->values_.key_;

            node->right = DeleteNode(node->right, tmp->values_.key_, node_deleted);
        }
    }

    if (!node) return node;

    node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));

    int balance = GetBalanceFactor(node);

    if (balance > 1 && GetHeight(node->left) >= 0) return RotateRight(node);
    if (balance > 1 && GetBalanceFactor(node->left) < 0) {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
    }
    if (balance < -1 && GetBalanceFactor(node->right) <= 0) return RotateLeft(node);
    if (balance < -1 && GetBalanceFactor(node->right) > 0) {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
    }

    return node;
}

SelfBalancingBinarySearchTree::Node *SelfBalancingBinarySearchTree::MinValueNode(Node *node) {
    Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left) current = current->left;

    return current;
}

void SelfBalancingBinarySearchTree::FindKeysRecursively(Node *node, std::vector<std::string> &keys) {
    if (node) {
        keys.push_back(node->values_.key_);
        FindKeysRecursively(node->left, keys);
        FindKeysRecursively(node->right, keys);
    }
}

SelfBalancingBinarySearchTree::Node *SelfBalancingBinarySearchTree::FindNodeByKey(std::string &key) {
    if (!root_) return nullptr;
    Node *tmp = root_;
    while (true) {
        if (key == tmp->values_.key_) {
            return tmp;
        }
        if (key < tmp->values_.key_ && tmp->left) {
            tmp = tmp->left;
        } else if (tmp->right) {
            tmp = tmp->right;
        } else {
            return nullptr;
        }
    }
}

int &SelfBalancingBinarySearchTree::GetNodeEx(std::string &key) { return FindNodeByKey(key)->values_.ex_; }

void SelfBalancingBinarySearchTree::FindKeyByValuesRecursively(Node *node, Values &values,
                                                               std::vector<std::string> &return_vector) {
    if (node) {
        if ((values.last_name_ == "-" || values.last_name_ == node->values_.last_name_) &&
            (values.first_name_ == "-" || values.first_name_ == node->values_.first_name_) &&
            (values.year_of_birth_ == -1 || values.year_of_birth_ == node->values_.year_of_birth_) &&
            (values.city_ == "-" || values.city_ == node->values_.city_) &&
            (values.number_of_coins_ == -1 || values.number_of_coins_ == node->values_.number_of_coins_)) {
            return_vector.push_back(node->values_.key_);
        }
        FindKeyByValuesRecursively(node->left, values, return_vector);
        FindKeyByValuesRecursively(node->right, values, return_vector);
    }
}

void SelfBalancingBinarySearchTree::GetAllValuesRecursively(Node *node,
                                                            std::vector<Values *> &return_vector) {
    if (node) {
        return_vector.push_back(&node->values_);
        GetAllValuesRecursively(node->left, return_vector);
        GetAllValuesRecursively(node->right, return_vector);
    }
}

void SelfBalancingBinarySearchTree::ExportNodesRecursively(Node *node, std::fstream &fs, int &counter) {
    if (node) {
        ExportValues(&node->values_, fs, counter);
        ExportNodesRecursively(node->left, fs, counter);
        ExportNodesRecursively(node->right, fs, counter);
    }
}

void SelfBalancingBinarySearchTree::PrintWholeTree(Node *node, Node *parent) {
    if (node) {
        if (parent) {
            if (node == parent->left) {
                std::cout << node->values_.key_ << " is left child of " << parent->values_.key_ << std::endl;
            } else {
                std::cout << node->values_.key_ << " is right child of " << parent->values_.key_ << std::endl;
            }
        } else {
            std::cout << node->values_.key_ << " is root" << std::endl;
        }
        if (node->left) {
            PrintWholeTree(node->left, node);
        }
        if (node->right) {
            PrintWholeTree(node->right, node);
        }
    }
}
}  // namespace s21