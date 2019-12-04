#pragma once

#include "../general.h"

class NumberIterator : iterator<forward_iterator_tag, int> {
public:
    int v;

    NumberIterator(int v) : v(v) {}

    operator int &() { return v; }

    int operator*() { return v; }
};

class Range : pii {
public:
    Range(int begin, int end) : pii(begin, end) {}

    Range(int n) : pii(0, n) {}

    NumberIterator begin() {
        return first;
    }

    NumberIterator end() {
        return second;
    }
};
