#pragma once

#include "range.h"

class ReverseNumberIterator : public NumberIterator {
public:
    ReverseNumberIterator(int v) : NumberIterator(v) {}

    ReverseNumberIterator& operator++() {
        --v;
        return *this;
    }
};

class RevRange : pii {
public:
    RevRange(int begin, int end) : pii(begin - 1, end - 1) {}

    RevRange(int n) : pii(n - 1, -1) {}

    ReverseNumberIterator begin() {
        return first;
    }

    ReverseNumberIterator end() {
        return second;
    }
};
