#pragma once

#include "../../general.h"

class BaseEdge {
public:
    const int to;
    int id;

    BaseEdge(int, int to) : to(to) {
    }

    BaseEdge* transposed() { return nullptr; }
    BaseEdge* reverse() { return nullptr; }
};

