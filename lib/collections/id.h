#pragma once

#include "../general.h"
#include "arr.h"

template <typename T, class Map = map<T, int>>
class Id {
    Map map;
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

    arr<T> byId() const {
        arr<T> result(next);
        for (const auto& entry : map) {
            result[entry.second] = entry.first;
        }
        return result;
    }
};
