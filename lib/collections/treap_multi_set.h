#pragma once

#include "treap.h"

struct MultiSizeData {
public:
    int curSize = 1;
    int size;

    template <typename T>
    void update(Node<T, MultiSizeData>* left, Node<T, MultiSizeData>* right) {
        size = curSize + (left == nullptr ? 0 : left->data.size) + (right == nullptr ? 0 : right->data.size);
    }
};

template <typename T>
struct TreapMultiSet {
    using TNode = Node<T, MultiSizeData>;
    mutable TNode* root = nullptr;

    bool addToLeftmost(TNode* node, const T& key) {
        if (node->left == nullptr) {
            if (node->key == key) {
                node->data.curSize++;
                node->dataUpdate();
                return true;
            }
            return false;
        } else if (addToLeftmost(node->left, key)) {
            node->dataUpdate();
            return true;
        }
        return false;
    }

    bool insert(const T& element) {
        auto* node = new TNode(element);
        if (root == nullptr) {
            root = node;
            return true;
        } else {
            auto split = root->split(element);
            if (split.second != nullptr) {
                if (addToLeftmost(split.second, element)) {
                    root = merge(split.first, split.second);
                    return true;
                }
            }
            root = merge(split.first, node);
            root = merge(root, split.second);
            return true;
        }
    }

    bool remove(const T& element) {
        if (root == nullptr) {
            return false;
        } else {
            auto split = root->split(element);
            if (split.second == nullptr) {
                root = split.first;
                return false;
            }
            auto split2 = split.second->split(element, true);
            if (split2.first != nullptr && split2.first->data.curSize > 1) {
                split2.first->data.curSize--;
                split2.first->dataUpdate();
                root = merge(split2.first, split2.second);
                root = merge(split.first, root);
            } else {
                root = merge(split.first, split2.second);
            }
            return split2.first != nullptr;
        }
    }

    int index(const T& element) const {
        auto split = root->split(element);
        if (split.second == nullptr || split.second->leftmost() != element) {
            root = merge(split.first, split.second);
            return -1;
        }
        int res = split.first == nullptr ? 0 : split.first->data.size;
        root = merge(split.first, split.second);
        return res;
    }

    int toLeft(const T& element) const {
        if (root == nullptr) {
            return 0;
        }
        auto split = root->split(element);
        int res = split.first == nullptr ? 0 : split.first->data.size;
        root = merge(split.first, split.second);
        return res;
    }

    int toRight(const T& element) const {
        if (root == nullptr) {
            return 0;
        }
        auto split = root->split(element, true);
        int res = split.second == nullptr ? 0 : split.second->data.size;
        root = merge(split.first, split.second);
        return res;
    }

    bool contains(const T& element) const {
        return index(element) != -1;
    }

    int size() const { return root == nullptr ? 0 : root->data.size; }

    const T& get(int index) const {
#ifdef LOCAL
        int sz = size();
        if (index < 0 || index >= sz) {
            throw "Index out of bounds";
        }
#endif
        TNode* node = root;
        while (true) {
            int leftSize = node->left == nullptr ? 0 : node->left->data.size;
            if (leftSize == index) {
                return node->key;
            }
            if (leftSize > index) {
                node = node->left;
            } else {
                index -= leftSize + 1;
                node = node->right;
            }
        }
    }

};
