#pragma once

#include "../../general.h"
#include "../graph.h"
#include "../../collections/arr.h"
#include "../../collections/indexed_heap.h"

template <class Edge, typename W>
arr<pair<W, pair<int, Edge*>>> dijkstra(Graph<Edge>& graph, int source) {
    int n = graph.vertexCount;
    arr<pair<W, pair<int, Edge*>>> res(n, {numeric_limits<W>::max(), make_pair(-1, nullptr)});
    res[source].first = 0;
    IndexedHeap heap(n, [&](int a, int b) -> bool {
        return res[a].first < res[b].first;
    });
    heap.push(source);
    while (!heap.empty()) {
        int cur = heap.pop();
        for (auto& e : graph[cur]) {
            int next = e.to;
            W total = e.weight + res[cur].first;
            if (res[next].first > total) {
                res[next].first = total;
                int at = heap.at(next);
                if (at == -1) {
                    heap.push(next);
                } else {
                    heap.siftUp(at);
                }
                res[next].second = {cur, &e};
            }
        }
    }
    return res;
}
