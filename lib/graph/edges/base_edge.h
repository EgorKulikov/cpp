#pragma once

#include "../../general.h"

class BaseEdge {
public:
    const int from;
    const int to;
    int id;

    BaseEdge(int from, int to) : from(from), to(to) {
    }

    BaseEdge* transposed() { return nullptr; }
    BaseEdge* reverse() { return nullptr; }
};

