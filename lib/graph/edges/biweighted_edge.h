#pragma once

#include "../../general.h"

template <typename W>
class BiWeightedEdge {
private:
    BiWeightedEdge<W>* transposedEdge;

public:
    const int from;
    const int to;
    W weight;
    int id;

    BiWeightedEdge(int from, int to, W weight) : from(from), to(to), weight(weight) {
        transposedEdge = new BiWeightedEdge(this);
    }

    BiWeightedEdge<W>* transposed() { return transposedEdge; }
    BiWeightedEdge<W>* reverse() { return nullptr; }

private:
    BiWeightedEdge(BiWeightedEdge<W>* transposed) : from(transposed->to), to(transposed->from), weight(transposed->weight) {
        transposedEdge = transposed;
    }
};

