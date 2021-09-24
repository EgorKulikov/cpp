#pragma once

#include "../../general.h"
#include "biedge.h"

template <typename C>
class FlowEdge : public BiEdge {
public:
    const static bool reversable = true;
    C capacity;
#ifdef LOCAL
    bool direct;
#endif

    FlowEdge(int to, int id, C capacity) : BiEdge(to, id), capacity(capacity) {
#ifdef LOCAL
        direct = true;
#endif
    }

    FlowEdge<C> reverseEdge(int from) {
        auto edge = FlowEdge<C>(from, id, 0);
#ifdef LOCAL
        edge.direct = false;
#endif
        return edge;
    }

    FlowEdge<C>& reverseEdge(Graph<FlowEdge<C>>& graph) const {
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

#ifdef LOCAL
template <typename C>
void printFlow(Output& out, Graph<FlowEdge<C>>& graph) {
    for (int i : range(graph.vertexCount)) {
        for (auto& e : graph[i]) {
            if (e.direct && e.flow(graph)) {
                out.template printLine(i, e.to, e.flow(graph));
            }
        }
    }
}
#endif
