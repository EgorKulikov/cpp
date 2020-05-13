#pragma once

#include "../../general.h"

template <typename W, typename C>
class WeightedFlowEdge {
private:
    WeightedFlowEdge<W, C>* reverseEdge;

public:
    const int to;
    W weight;
    C capacity;
    int id;

    WeightedFlowEdge(int from, int to, W weight, C capacity) : to(to), weight(weight), capacity(capacity) {
        reverseEdge = new WeightedFlowEdge(this, from);
    }

    WeightedFlowEdge<W, C>* transposed() { return nullptr; }
    WeightedFlowEdge<W, C>* reverse() { return reverseEdge; }
    void push(C flow) {
        capacity -= flow;
        reverseEdge->capacity += flow;
    }
    C flow() const {
        return reverseEdge->capacity;
    }

private:
    WeightedFlowEdge(WeightedFlowEdge<W, C>* reverse, int from) : to(from), weight(-reverse->weight), capacity(0) {
        reverseEdge = reverse;
    }
};

