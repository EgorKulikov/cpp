#pragma once

#include "../../general.h"
#include "biedge.h"

template <typename W>
class BiWeightedEdge : public BiEdge {
public:
    const static bool reversable = true;
    W weight;

    BiWeightedEdge(int to, int id, W weight) : BiEdge(to, id), weight(weight) {
    }

    BiWeightedEdge reverseEdge(int from) {
        return BiWeightedEdge(from, id, weight);
    }

    BiWeightedEdge<W>& reverseEdge(Graph<BiWeightedEdge<W>>& graph) {
        return graph[to][rev];
    }
};

