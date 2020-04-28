#pragma once

#include "../general.h"
#include "arr.h"

template <typename Value, Value defaultValue = 0>
class ReadOnlySegmentTree {
private:
    const int size;
    function<Value(Value, Value)> joinValue;
    arr<Value> value;

    void init(int root, int left, int right, const arr<Value>& array) {
        if (left + 1 == right) {
            value[root] = array[left];
        } else {
            int mid = (left + right) >> 1;
            init(2 * root + 1, left, mid, array);
            init(2 * root + 2, mid, right, array);
            value[root] = joinValue(value[2 * root + 1], value[2 * root + 2]);
        }
    }

    Value query(int root, int left, int right, int from, int to) const {
        if (left >= from && right <= to) {
            return value[root];
        }
        if (right <= from || left >= to) {
            return defaultValue;
        }
        int mid = (left + right) >> 1;
        Value lValue = query(2 * root + 1, left, mid, from, to);
        Value rValue = query(2 * root + 2, mid, right, from, to);
        return joinValue(lValue, rValue);
    }

public:
    ReadOnlySegmentTree(const arr<Value>& array, function<Value(Value, Value)> joinValue) :
            size(array.size()), joinValue(joinValue) {
        int vertexSize = size * 4;
        value = arr<Value>(vertexSize);
        if (size > 0) {
            init(0, 0, size, array);
        }
    }

    Value query(int from, int to) const {
        return query(0, 0, size, max(0, from), to);
    }
};
