//
// Created by kulikov on 11/7/2019.
//

#include <functional>

#ifndef JHELPER_EXAMPLE_PROJECT_INTERVAL_TREE_H
#define JHELPER_EXAMPLE_PROJECT_INTERVAL_TREE_H

#include "../general.h"

template<typename Value, typename Delta, Value defaultValue = 0, Delta defaultDelta = 0>
class IntervalTree {
private:
    const int size;
    const function<Value(Value, Value)> &joinValue;
    const function<Delta(Delta, Delta)> &joinDelta;
    const function<Value(Value, Delta, int, int)> &accumulate;
    const function<Value(int)> &initValue;
    vector<Value> value;
    vector<Delta> delta;

    void init(int root, int left, int right) {
        if (left + 1 == right) {
            value[root] = initValue(left);
        } else {
            int mid = (left + right) >> 1;
            initValue(2 * root + 1, left, mid);
            initValue(2 * root + 2, mid, right);
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
    IntervalTree(int size, const function<Value(Value, Value)> &joinValue,
                 const function<Delta(Delta, Delta)> &joinDelta,
                 function<Value(Value, Delta, int, int)> &accumulate,
                 const function<Value(int)> &initValue = [](int at) -> Value { return defaultValue; }) :
            size(size), joinValue(joinValue), joinDelta(joinDelta), accumulate(accumulate), initValue(initValue) {
        int vertexSize = size * 4;
        value = vector<Value>(vertexSize);
        delta = vector<Delta>(vertexSize, defaultDelta);
        init(0, 0, size);
    }

    void update(int from, int to, Delta delta) {
        update(0, 0, size, from, to, delta);
    }

    Value query(int from, int to) {
        return query(0, 0, size, from, to);
    }
};


#endif //JHELPER_EXAMPLE_PROJECT_INTERVAL_TREE_H
