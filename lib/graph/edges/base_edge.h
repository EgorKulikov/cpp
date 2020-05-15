#pragma once

#include "../../general.h"
#include "../graph.h"

class BaseEdge {
public:
    const static bool reversable = false;
    int to;
    int id;

    BaseEdge(int to, int id) : to(to), id(id) {
    }

    BaseEdge reverseEdge(int) {
        throw "Unsupported operation exception";
    }

    void setReverseId(int) {
        throw "Unsupported operation exception";
    }
};

