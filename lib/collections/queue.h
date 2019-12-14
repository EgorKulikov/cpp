#pragma once

#include "../general.h"

template<typename T>
class que : public queue<T> {
public:
    que() : queue<T>() {}
    que(const que<T>& q) : queue<T>(q) {}
    que(que<T>&& q) noexcept : queue<T>(move(q)) {}

    T& pop() {
        T& res = queue<T>::front();
        queue<T>::pop();
        return res;
    }
};
