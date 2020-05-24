#pragma once

#include "../general.h"

random_device rd;
mt19937_64 gen(rd());

template<typename T, typename Data>
class Node {
public:
    ll priority = gen();
    T key;
    Data data;
    Node *left;
    Node *right;

    Node(T key, Data data = Data(), Node *left = nullptr, Node *right = nullptr) : key(key), data(data), left(left), right(right) {
        dataUpdate();
    }

    void dataUpdate() {
        data.update(left, right);
    }

    pair<Node<T, Data>*, Node<T, Data>*> split(T splitKey, bool toLeft = false) {
        if (toLeft ? key <= splitKey : key < splitKey) {
            auto result = right == nullptr ? make_pair(nullptr, nullptr) : right->split(splitKey, toLeft);
            right = result.first;
            dataUpdate();
            result.first = this;
            return result;
        }
        auto result = left == nullptr ? make_pair(nullptr, nullptr) : left->split(splitKey, toLeft);
        left = result.second;
        dataUpdate();
        result.second = this;
        return result;
    }

    Node<T, Data>* leftmost() {
        if (left == nullptr) {
            return this;
        }
        return left->leftmost();
    }
};

template<typename T, typename Data>
Node<T, Data> *merge(Node<T, Data> *left, Node<T, Data> *right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        left->dataUpdate();
        return left;
    }
    right->left = merge(left, right->left);
    right->dataUpdate();
    return right;
}

class SizeData {
public:
    int size;

    template <typename T>
    void update(Node<T, SizeData>* left, Node<T, SizeData>* right) {
        size = 1 + (left == nullptr ? 0 : left->data.size) + (right == nullptr ? 0 : right->data.size);
    }
};

template<typename Data>
class KeylessTreapNode {
public:
    ll priority = gen();
    Data data;
    KeylessTreapNode *left;
    KeylessTreapNode *right;
    int size;

    KeylessTreapNode(Data data, KeylessTreapNode *left = nullptr, KeylessTreapNode *right = nullptr) : data(data), left(left), right(right) {
        dataUpdate();
    }

    void dataUpdate() {
        size = 1 + (left == nullptr ? 0 : left->size) + (right == nullptr ? 0 : right->size);
        data.update(left, right);
    }

    pair<KeylessTreapNode<Data>*, KeylessTreapNode<Data>*> split(int leftSize) {
        dataUpdate();
        int lSize = left == nullptr ? 0 : left->size;
        if (lSize >= leftSize) {
            auto result = left == nullptr ? make_pair(nullptr, nullptr) : left->split(leftSize);
            left = result.second;
            dataUpdate();
            result.second = this;
            return result;
        } else {
            leftSize -= lSize + 1;
            auto result = right == nullptr ? make_pair(nullptr, nullptr) : right->split(leftSize);
            right = result.first;
            dataUpdate();
            result.first = this;
            return result;
        }
    }

    KeylessTreapNode<Data>* leftmost() {
        dataUpdate();
        if (left == nullptr) {
            return this;
        }
        return left->leftmost();
    }
};

template<typename Data>
KeylessTreapNode<Data> *merge(KeylessTreapNode<Data> *left, KeylessTreapNode<Data> *right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    if (left->priority > right->priority) {
        left->dataUpdate();
        left->right = merge(left->right, right);
        left->dataUpdate();
        return left;
    }
    right->dataUpdate();
    right->left = merge(left, right->left);
    right->dataUpdate();
    return right;
}
