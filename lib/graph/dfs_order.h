#pragma once

#include "../general.h"
#include "graph.h"
#include "../collections/arr.h"

class DFSOrder {
public:
    arri position;
    arri end;

    template <class Edge>
    DFSOrder(Graph<Edge>& graph, int root = 0) {
        int count = graph.vertexCount;
        position = arri(count);
        end = arri(count);
        arri edge(count, 0);
        arri stack(count);
        arri last(count);
        stack[0] = root;
        last[root] = -1;
        int size = 1;
        position[root] = 0;
        int index = 0;
        while (size > 0) {
            int current = stack[size - 1];
            int& cEdge = edge[current];
            if (cEdge == graph[current].size()) {
                end[current] = index + 1;
                size--;
            } else {
                int next = graph[current][cEdge].to;
                if (next == last[current]) {
                    cEdge++;
                    continue;
                }
                cEdge++;
                position[next] = ++index;
                last[next] = current;
                stack[size++] = next;
            }
        }
    }
};
