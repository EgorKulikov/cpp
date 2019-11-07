//
// Created by egor on 04.11.2019.
//

#ifndef JHELPER_EXAMPLE_PROJECT_GRAPH_H
#define JHELPER_EXAMPLE_PROJECT_GRAPH_H

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
class BidirectionalWeightedEdge {
private:
    BidirectionalWeightedEdge<W>* transposedEdge;

public:
    const int from;
    const int to;
    W weight;
    int id;

    BidirectionalWeightedEdge(int from, int to, W weight) : from(from), to(to), weight(weight) {
        transposedEdge = new BidirectionalWeightedEdge(this);
    }

    BidirectionalWeightedEdge<W>* transposed() { return transposedEdge; }
    BidirectionalWeightedEdge<W>* reverse() { return nullptr; }

private:
    BidirectionalWeightedEdge(BidirectionalWeightedEdge<W>* transposed) : from(transposed->to), to(transposed->from), weight(transposed->weight) {
        transposedEdge = transposed;
    }
};

class SimpleEdge {
public:
    const int from;
    const int to;
    int id;

    SimpleEdge(int from, int to) : from(from), to(to) {
    }

    SimpleEdge* transposed() { return nullptr; }
    SimpleEdge* reverse() { return nullptr; }
};

class BidirectionalEdge {
private:
    BidirectionalEdge* transposedEdge;

public:
    const int from;
    const int to;
    int id;

    BidirectionalEdge(int from, int to) : from(from), to(to) {
        transposedEdge = new BidirectionalEdge(*this);
    }

    BidirectionalEdge* transposed() { return transposedEdge; }
    BidirectionalEdge* reverse() { return nullptr; }

private:
    BidirectionalEdge(BidirectionalEdge* transposed) : from(transposed->to), to(transposed->from) {
        transposedEdge = transposed;
    }
};

template <class Edge>
class Graph {
public:
    int vertexCount;
    int edgeCount = 0;
    vector<vector<Edge*> > edges;

    Graph(int vertexCount) : vertexCount(vertexCount) {
        edges.resize(vertexCount);
    }

    void addEdge(Edge* edge) {
        edge->id = edgeCount;
        edges[edge->from].push_back(edge);
        if (edge->reverse() != nullptr) {
            edge->reverse()->id = edgeCount;
            edges[edge->reverse()->from].push_back(edge->reverse());
        }
        if (edge->transposed() != nullptr) {
            edges[edge->transposed()->from].push_back(edge->transposed());
            edge->transposed()->id = edgeCount;
            if (edge->transposed()->reverse() != nullptr) {
                edges[edge->transposed()->reverse()->from].push_back(edge->transposed()->reverse());
                edge->transposed()->reverse()->id = edgeCount;
            }
        }
        edgeCount++;
    }
};

typedef FlowEdge<ll> LongFlowEdge;
typedef WeightedEdge<ll> LongWeightedEdge;
typedef FlowEdge<int> IntFlowEdge;
typedef WeightedEdge<int> IntWeightedEdge;
typedef BidirectionalWeightedEdge<ll> LongBiWeightedEdge;
typedef BidirectionalWeightedEdge<int> IntBiWeightedEdge;

#endif //JHELPER_EXAMPLE_PROJECT_GRAPH_H
