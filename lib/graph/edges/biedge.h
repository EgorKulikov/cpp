#pragma once

#include "../../general.h"

class BiEdge {
private:
    BiEdge* transposedEdge;

public:
    const int to;
    int id;

    BiEdge(int from, int to) : to(to) {
        transposedEdge = new BiEdge(this, from);
    }

    BiEdge* transposed() { return transposedEdge; }
    BiEdge* reverse() { return nullptr; }

private:
    BiEdge(BiEdge* transposed, int from) : to(from) {
        transposedEdge = transposed;
    }
};

