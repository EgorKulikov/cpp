#pragma once

#include "treap.h"

template <typename T>
struct TreapSet {
    using TNode = Node<T, SizeData>;
    mutable TNode* root = nullptr;

    bool insert(const T& element) {
        auto* node = new TNode(element);
        if (root == nullptr) {
            root = node;
            return true;
        } else {
            auto split = root->split(element);
            if (split.second != nullptr && split.second->leftmost()->key == element) {
                root = merge(split.first, split.second);
                return false;
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
            root = merge(split.first, split2.second);
            return split2.first != nullptr;
        }
    }

    int index(const T& element) const {
        auto split = root->split(element);
        if (split.second == nullptr || split.second->leftmost()->key != element) {
            root = merge(split.first, split.second);
            return -1;
        }
        int res = split.first == nullptr ? 0 : split.first->data.size;
        root = merge(split.first, split.second);
        return res;
    }

    int toLeft(const T& element) const {
        auto split = root->split(element);
        int res = split.first == nullptr ? 0 : split.first->data.size;
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
