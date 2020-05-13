#pragma once

#include "../../general.h"

template <typename W>
class BiWeightedEdge {
private:
    BiWeightedEdge<W>* transposedEdge;

public:
    const int to;
    W weight;
    int id;

    BiWeightedEdge(int from, int to, W weight) : to(to), weight(weight) {
        transposedEdge = new BiWeightedEdge(this, from);
    }

    BiWeightedEdge<W>* transposed() { return transposedEdge; }
    BiWeightedEdge<W>* reverse() { return nullptr; }

private:
    BiWeightedEdge(BiWeightedEdge<W>* transposed, int from) : to(from), weight(transposed->weight) {
        transposedEdge = transposed;
    }
};

