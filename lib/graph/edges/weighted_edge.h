#pragma once

#include "../../general.h"

template <typename W>
class WeightedEdge {
public:
    const int from;
    const int to;
    W weight;
    int id;

    WeightedEdge(int from, int to, W weight) : from(from), to(to), weight(weight) {
    }

    WeightedEdge<W>* transposed() { return nullptr; }
    WeightedEdge<W>* reverse() { return nullptr; }
};

