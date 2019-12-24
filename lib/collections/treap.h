#pragma once

#include "../general.h"

random_device rd;
mt19937_64 gen(rd());

template<typename T, typename Data>
class TreapNode {
public:
    ll priority = gen();
    T key;
    Data data;
    TreapNode *left;
    TreapNode *right;

    TreapNode(T key, Data data = Data(), TreapNode *left = nullptr, TreapNode *right = nullptr) : key(key), data(data), left(left), right(right) {
        dataUpdate();
    }

    void dataUpdate() {
        data.update(left == nullptr ? nullptr : &left->data, right == nullptr ? nullptr : &right->data);
    }

    pair<TreapNode<T, Data>*, TreapNode<T, Data>*> split(T splitKey) {
        if (key < splitKey) {
            auto result = right == nullptr ? make_pair(nullptr, nullptr) : right->split(splitKey);
            right = result.first;
            dataUpdate();
            result.first = this;
            return result;
        }
        auto result = left == nullptr ? make_pair(nullptr, nullptr) : left->split(splitKey);
        left = result.second;
        dataUpdate();
        result.second = this;
        return result;
    }

    TreapNode<T, Data>* leftmost() {
        if (left == nullptr) {
            return this;
        }
        return left->leftmost();
    }
};

template<typename T, typename Data>
TreapNode<T, Data> *merge(TreapNode<T, Data> *left, TreapNode<T, Data> *right) {
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

    void update(SizeData* left, SizeData* right) {
        size = 1 + (left == nullptr ? 0 : left->size) + (right == nullptr ? 0 : right->size);
    }
};
