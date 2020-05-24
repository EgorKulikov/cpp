#pragma once

#include "../general.h"

template<typename T>
class que : public queue<T> {
    using parent = queue<T>;
public:
    que() : parent() {}
    que(const que<T>& q) : parent(q) {}
    que(que<T>&& q) noexcept : parent(move(q)) {}

    T pop() {
#ifdef LOCAL
        if (parent::empty()) {
            throw "Pop on empty queue";
        }
#endif
        T res = parent::front();
        parent::pop();
        return res;
    }

    que<T>& operator =(que<T>&& __x) noexcept {
        parent::operator=(__x);
        return *this;
    }

    que<T>& operator =(const que<T>& __x) {
        parent::operator=(__x);
        return *this;
    }
};

using qi = que<int>;
