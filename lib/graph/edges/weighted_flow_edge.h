#pragma once

#include "../../general.h"
#include "flow_edge.h"

template <typename W, typename C>
class WeightedFlowEdge : public FlowEdge<C> {
public:
    const static bool reversable = true;
    W weight;

    WeightedFlowEdge(int to, int id, W weight, C capacity) : FlowEdge<C>(to, id, capacity), weight(weight) {
    }

    WeightedFlowEdge<W, C> reverseEdge(int from) {
        auto edge = WeightedFlowEdge<W, C>(from, BaseEdge::id, -weight, 0);
#ifdef LOCAL
        edge.direct = false;
#endif
        return edge;
    }

    WeightedFlowEdge<W, C>& reverseEdge(Graph<WeightedFlowEdge<W, C>>& graph) const {
        return graph[BaseEdge::to][BiEdge::rev];
    }

    void push(Graph<WeightedFlowEdge<W, C>>& graph, C flow) {
#ifdef LOCAL
        if (flow < 0 || flow > FlowEdge<C>::capacity) {
            throw "Invalid flow";
        }
#endif
        FlowEdge<C>::capacity -= flow;
        reverseEdge(graph).FlowEdge<C>::capacity += flow;
    }

    C flow(Graph<WeightedFlowEdge<W, C>>& graph) const {
        return reverseEdge(graph).FlowEdge<C>::capacity;
    }
};

#ifdef LOCAL
#include "../../io/output.h"

template <typename W, typename C>
void printFlow(Output& out, Graph<WeightedFlowEdge<W, C>>& graph) {
    for (int i : range(graph.vertexCount)) {
        for (auto& e : graph[i]) {
            if (e.direct && e.flow(graph)) {
                out.template printLine(i, e.to, e.flow(graph));
            }
        }
    }
}
#endif
