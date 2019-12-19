#pragma once

#include "../general.h"

template <typename W, typename C>
class WeightedFlowEdge {
private:
    WeightedFlowEdge<W, C>* reverseEdge;

public:
    const int from;
    const int to;
    W weight;
    C capacity;
    int id;

    WeightedFlowEdge(int from, int to, W weight, C capacity) : from(from), to(to), weight(weight), capacity(capacity) {
        reverseEdge = new WeightedFlowEdge(this);
    }

    WeightedFlowEdge<W, C>* transposed() { return nullptr; }
    WeightedFlowEdge<W, C>* reverse() { return reverseEdge; }
    void push(C flow) {
        capacity -= flow;
        reverseEdge->capacity += flow;
    }
    C flow() const {
        return reverseEdge->capacity;
    }

private:
    WeightedFlowEdge(WeightedFlowEdge<W, C>* reverse) : from(reverse->to), to(reverse->from), weight(-reverse->weight), capacity(0) {
        reverseEdge = reverse;
    }
};

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

template <typename W>
class WeightedEdge {
public:
    const int from;
    const int to;
    W weight;
    int id;

    WeightedEdge(int from, int to, W weight) : from(from), to(to), weight(weight) {
    }

    WeightedEdge<W>* transposed() { return nullptr; }
    WeightedEdge<W>* reverse() { return nullptr; }
};

template <typename W>
class BiWeightedEdge {
private:
    BiWeightedEdge<W>* transposedEdge;

public:
    const int from;
    const int to;
    W weight;
    int id;

    BiWeightedEdge(int from, int to, W weight) : from(from), to(to), weight(weight) {
        transposedEdge = new BiWeightedEdge(this);
    }

    BiWeightedEdge<W>* transposed() { return transposedEdge; }
    BiWeightedEdge<W>* reverse() { return nullptr; }

private:
    BiWeightedEdge(BiWeightedEdge<W>* transposed) : from(transposed->to), to(transposed->from), weight(transposed->weight) {
        transposedEdge = transposed;
    }
};

class BaseEdge {
public:
    const int from;
    const int to;
    int id;

    BaseEdge(int from, int to) : from(from), to(to) {
    }

    BaseEdge* transposed() { return nullptr; }
    BaseEdge* reverse() { return nullptr; }
};

class BiEdge {
private:
    BiEdge* transposedEdge;

public:
    const int from;
    const int to;
    int id;

    BiEdge(int from, int to) : from(from), to(to) {
        transposedEdge = new BiEdge(this);
    }

    BiEdge* transposed() { return transposedEdge; }
    BiEdge* reverse() { return nullptr; }

private:
    BiEdge(BiEdge* transposed) : from(transposed->to), to(transposed->from) {
        transposedEdge = transposed;
    }
};

template <class Edge>
class Graph {
public:
    int vertexCount;
    int edgeCount = 0;
private:
    arr<vec<Edge*> > edges;

public:
    Graph(int vertexCount) : vertexCount(vertexCount), edges(vertexCount, vec<Edge*>()) {}

    void addEdge(Edge* edge) {
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

    vec<Edge*>& operator [](int at) {
        return edges[at];
    }
};
