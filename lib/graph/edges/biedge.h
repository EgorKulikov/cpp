#pragma once

#include "../../general.h"
#include "base_edge.h"
#include "../graph.h"

class BiEdge : public BaseEdge {
public:
    const static bool reversable = true;
    int rev;

    BiEdge(int to, int id) : BaseEdge(to, id) {
    }

    void setReverseId(int revId) {
        rev = revId;
    }

    BiEdge reverseEdge(int from) {
        return BiEdge(from, id);
    }

    BiEdge& reverseEdge(Graph<BiEdge>& graph) {
        return graph[to][rev];
    }
};
