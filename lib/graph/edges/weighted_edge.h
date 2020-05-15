#pragma once

#include "../../general.h"
#include "base_edge.h"

template <typename W>
class WeightedEdge : public BaseEdge {
public:
    const static bool reversable = false;
    W weight;

    WeightedEdge(int to, int id, W weight) : BaseEdge(to, id), weight(weight) {
    }
};
