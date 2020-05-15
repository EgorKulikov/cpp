#pragma once

#include "../../general.h"
#include "biedge.h"

template <typename C>
class FlowEdge : public BiEdge {
public:
    const static bool reversable = true;
    C capacity;

    FlowEdge(int to, int id, C capacity) : BiEdge(to, id), capacity(capacity) {
    }

    FlowEdge<C> reverseEdge(int from) {
        return FlowEdge<C>(from, id, 0);
    }

    FlowEdge<C>& reverseEdge(Graph<FlowEdge<C>>& graph) {
        return graph[to][rev];
    }

    void push(Graph<FlowEdge<C>>& graph, C flow) {
#ifdef LOCAL
        if (flow < 0 || flow > capacity) {
            throw "Invalid flow";
        }
#endif
        capacity -= flow;
        reverseEdge(graph).capacity += flow;
    }

    C flow(Graph<FlowEdge<C>>& graph) const {
        return reverseEdge(graph).capacity;
    }
};
