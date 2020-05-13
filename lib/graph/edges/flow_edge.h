#pragma once

#include "../../general.h"

template <typename C>
class FlowEdge {
private:
    FlowEdge<C>* reverseEdge;

public:
    const int to;
    C capacity;
    int id;

    FlowEdge(int from, int to, C capacity) : to(to), capacity(capacity) {
        reverseEdge = new FlowEdge(this, from);
    }

    FlowEdge<C>* transposed() { return nullptr; }
    FlowEdge<C>* reverse() { return reverseEdge; }
    void push(C flow) {
#ifdef LOCAL
        if (flow < 0 || flow > capacity) {
            throw "Invalid flow";
        }
#endif
        capacity -= flow;
        reverseEdge->capacity += flow;
    }
    C flow() const {
        return reverseEdge->capacity;
    }

private:
    FlowEdge(FlowEdge<C>* reverse, int from) : to(from), capacity(0) {
        reverseEdge = reverse;
    }
};

