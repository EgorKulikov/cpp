#pragma once

#include "../general.h"
#include "arr.h"

template<typename Value, typename Delta>
class SegmentTree {
    const int size;
public:
    Value defaultValue;
private:
    const Delta defaultDelta;
    function<Value(Value, Value)> joinValue;
    function<Delta(Delta, Delta)> joinDelta;
    function<Value(Value, Delta, int, int)> accumulate;
    arr<Value> value;
    arr<Delta> delta;

    void init(int root, int left, int right) {
        if (left + 1 == right) {
            value[root] = defaultValue;
        } else {
            int mid = (left + right) >> 1;
            init(2 * root + 1, left, mid);
            init(2 * root + 2, mid, right);
            value[root] = joinValue(value[2 * root + 1], value[2 * root + 2]);
        }
    }

    void apply(int root, Delta dlt, int left, int right) {
        value[root] = accumulate(value[root], dlt, left, right);
        delta[root] = joinDelta(delta[root], dlt);
    }

    void pushDown(int root, int left, int mid, int right) {
        apply(2 * root + 1, delta[root], left, mid);
        apply(2 * root + 2, delta[root], mid, right);
        delta[root] = defaultDelta;
    }

    void update(int root, int left, int right, int from, int to, Delta dlt) {
        if (left >= from && right <= to) {
            apply(root, dlt, left, right);
            return;
        }
        if (right <= from || left >= to) {
            return;
        }
        int mid = (left + right) >> 1;
        pushDown(root, left, mid, right);
        update(2 * root + 1, left, mid, from, to, dlt);
        update(2 * root + 2, mid, right, from, to, dlt);
        value[root] = joinValue(value[2 * root + 1], value[2 * root + 2]);
    }

    Value query(int root, int left, int right, int from, int to) {
        if (left >= from && right <= to) {
            return value[root];
        }
        if (right <= from || left >= to) {
            return defaultValue;
        }
        int mid = (left + right) >> 1;
        pushDown(root, left, mid, right);
        return joinValue(query(2 * root + 1, left, mid, from, to), query(2 * root + 2, mid, right, from, to));
    }

public:
    SegmentTree(int size, function<Value(Value, Value)> joinValue,
                function<Delta(Delta, Delta)> joinDelta,
                function<Value(Value, Delta, int, int)> accumulate,
                Value defaultValue = 0, Delta defaultDelta = 0 ) :
                size(size), joinValue(joinValue), joinDelta(joinDelta), accumulate(accumulate),
                defaultValue(defaultValue), defaultDelta(defaultDelta) {
        int vertexSize = size * 4;
        value = arr<Value>(vertexSize);
        delta = arr<Delta>(vertexSize, defaultDelta);
        if (size > 0) {
            init(0, 0, size);
        }
    }

    void update(int from, int to, Delta delta) {
        update(0, 0, size, max(0, from), to, delta);
    }

    Value query(int from, int to) {
        return query(0, 0, size, max(0, from), to);
    }
};
