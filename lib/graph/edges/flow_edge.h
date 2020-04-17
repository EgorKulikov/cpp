#pragma once

#include "../../general.h"

template <typename C>
class FlowEdge {
private:
    FlowEdge<C>* reverseEdge;

public:
    const int from;
    const int to;
    C capacity;
    int id;

    FlowEdge(int from, int to, C capacity) : from(from), to(to), capacity(capacity) {
        reverseEdge = new FlowEdge(this);
    }

    FlowEdge<C>* transposed() { return nullptr; }
    FlowEdge<C>* reverse() { return reverseEdge; }
    void push(C flow) {
        capacity -= flow;
        reverseEdge->capacity += flow;
    }
    C flow() const {
        return reverseEdge->capacity;
    }

private:
    FlowEdge(FlowEdge<C>* reverse) : from(reverse->to), to(reverse->from), capacity(0) {
        reverseEdge = reverse;
    }
};

