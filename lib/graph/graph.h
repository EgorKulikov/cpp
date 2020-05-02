#pragma once

#include "../general.h"

template <class Edge>
class Graph {
public:
    int vertexCount;
    int edgeCount = 0;
private:
    vector<basic_string<Edge*>> edges;

public:
    Graph(int vertexCount) : vertexCount(vertexCount), edges(vertexCount, basic_string<Edge*>()) {}

    void addEdge(Edge* edge) {
#ifdef LOCAL
        if (edge->from < 0 || edge->to < 0 || edge->from >= vertexCount || edge->to >= vertexCount) {
            throw "Out of bounds";
        }
#endif
        edge->id = edgeCount;
        edges[edge->from].push_back(edge);
        Edge* reverse = edge->reverse();
        if (reverse != nullptr) {
            reverse->id = edgeCount;
            edges[reverse->from].push_back(reverse);
        }
        Edge* transposed = edge->transposed();
        if (transposed != nullptr) {
            edges[transposed->from].push_back(transposed);
            transposed->id = edgeCount;
            Edge* transRev = transposed->reverse();
            if (transRev != nullptr) {
                edges[transRev->from].push_back(transRev);
                transRev->id = edgeCount;
            }
        }
        edgeCount++;
    }

    template <typename...Ts>
    void addEdge(Ts...args) {
        addEdge(new Edge(args...));
    }

    basic_string<Edge*>& operator [](int at) {
        return edges[at];
    }

    void addVertices(int count) {
        vertexCount += count;
        edges.resize(vertexCount);
    }
};
