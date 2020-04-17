#pragma once

#include "../../general.h"

class BiEdge {
private:
    BiEdge* transposedEdge;

public:
    const int from;
    const int to;
    int id;

    BiEdge(int from, int to) : from(from), to(to) {
        transposedEdge = new BiEdge(this);
    }

    BiEdge* transposed() { return transposedEdge; }
    BiEdge* reverse() { return nullptr; }

private:
    BiEdge(BiEdge* transposed) : from(transposed->to), to(transposed->from) {
        transposedEdge = transposed;
    }
};

