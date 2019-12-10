#pragma once

#include "../general.h"

template <typename T>
class Id {
    unordered_map<T, int> map;
    int next = 0;

public:
    int add(const T& element) {
        if (map.count(element) != 0) {
            return map[element];
        }
        map[element] = next++;
        return next - 1;
    }

    int operator[](const T& element) const {
        return map.find(element)->second;
    }

    int size() const {
        return next;
    }

    vector<T> byId() {
        vector<T> result(next);
        for (const auto& entry : map) {
            result[entry.second] = entry.first;
        }
        return result;
    }
};