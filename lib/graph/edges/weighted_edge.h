#pragma once

#include "../../general.h"

template <typename W>
class WeightedEdge {
public:
    const int to;
    W weight;
    int id;

    WeightedEdge(int, int to, W weight) : to(to), weight(weight) {
    }

    WeightedEdge<W>* transposed() { return nullptr; }
    WeightedEdge<W>* reverse() { return nullptr; }
};

