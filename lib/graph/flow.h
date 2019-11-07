//
// Created by kulikov on 11/7/2019.
//

#ifndef JHELPER_EXAMPLE_PROJECT_FLOW_H
#define JHELPER_EXAMPLE_PROJECT_FLOW_H

#include "graph.h"

template <class Edge, typename C>
class MaxFlow {
private:
    Graph<Edge>* graph;
    int source;
    int destination;
    queue<int> q;
    vi dist;
    vi nextEdge;
    C inf;

    MaxFlow(Graph<Edge>& graph, int source, int destination) : graph(&graph), source(source), destination(destination) {
        dist = vi(graph.vertexCount);
        nextEdge = vi(graph.vertexCount);
        inf = numeric_limits<C>().max();
    }

    void edgeDistances() {
        fill(all(dist), -1);
        dist[source] = 0;
        q.push(source);
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (auto edge : graph->edges[current]) {
                if (edge->capacity != 0) {
                    int next = edge->to;
                    if (dist[next] == -1) {
                        dist[next] = dist[current] + 1;
                        q.push(next);
                    }
                }
            }
        }
    }

    C dinicImpl(int source, C flow) {
        if (source == destination) {
            return flow;
        }
        if (flow == 0 || dist[source] == dist[destination]) {
            return 0;
        }
        C totalPushed = 0;
        while (nextEdge[source] < graph->edges[source].size()) {
            auto edge = graph->edges[source][nextEdge[source]];
            if (edge->capacity != 0 && dist[edge->to] == dist[source] + 1) {
                C pushed = dinicImpl(edge->to, min(flow, edge->capacity));
                if (pushed != 0) {
                    edge->push(pushed);
                    flow -= pushed;
                    totalPushed += pushed;
                    if (flow == 0) {
                        return totalPushed;
                    }
                }
            }
            nextEdge[source]++;
        }
        return totalPushed;
    }

public:
    C dinic() {
        C totalFlow = 0;
        while (true) {
            edgeDistances();
            if (dist[destination] == -1) {
                break;
            }
            fill(nextEdge.begin(), nextEdge.end(), 0);
            totalFlow += dinicImpl(source, inf);
        }
        return totalFlow;
    }

};

template <class Edge, typename C>
C dinic(Graph<Edge>& graph, int source, int destination) {
    return MaxFlow<Edge, C>(graph, source, destination).dinic();
}

#endif //JHELPER_EXAMPLE_PROJECT_FLOW_H
