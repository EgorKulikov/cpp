#pragma once

#include "general.h"

template <typename T>
class RecursiveFunction {
    T t;

public:
    RecursiveFunction(T&& t) : t(forward<T>(t)) {}

    template <typename... Args>
    auto operator() (Args&&... args) const {
        return t(*this, forward<Args>(args)...);
    }
};
