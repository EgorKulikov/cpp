#pragma once

#include "../../general.h"
#include "../graph.h"
#include "../../collections/arr.h"
#include "../../range/range.h"
#include "../../collections/indexed_heap.h"
#include "../../range/rev_range.h"
#include "../edges/weighted_flow_edge.h"

using Edge = WeightedFlowEdge<ll, ll>;

pair<ll, ll> minCostFlow(Graph<Edge>& orGraph, int source, int sink, bool onlyNegative = false) {
    ll inf = numeric_limits<ll>::max() / 2;
    ll large = 1ll << 40;

    int n = orGraph.vertexCount;
    arr<ll> p(n + 1, 0);
    p[n] = inf;

    Graph<Edge> graph(n + 1);
    arr<Edge*> base(orGraph.edgeCount, nullptr);
    arri corresponding(orGraph.edgeCount);
    for (int i : range(n)) {
        for (auto& e : orGraph[i]) {
            if (e.capacity > 0) {
                base[e.id] = &e;
                corresponding[e.id] = graph.addEdge(i, e.to, e.weight, 0).reverseEdge(graph).rev;
            }
        }
    }
    int back = graph.addEdge(sink, source, onlyNegative ? 0 : -large, 0).reverseEdge(graph).rev;
    for (int i : range(n)) {
        graph.addEdge(n, i, 0, 1);
    }

    arr<ll> dis(n + 1);
    IndexedHeap heap(n + 1, [&](int a, int b) -> bool {
        return dis[a] < dis[b];
    });
    arr<Edge*> pre(n + 1);
    auto c = [&](int from, Edge& e) -> ll {
        return p[from] + e.weight - p[e.to];
    };
    auto dijkstra = [&](int s) {
        fill(all(dis), inf);
        fill(all(pre), nullptr);
        dis[s] = 0;
        heap.push(s);

        while (!heap.empty()) {
            int u = heap.pop();
            ll w = dis[u];
            for (auto& e : graph[u]) {
                int v = e.to;
#ifdef LOCAL
                if (e.capacity > 0 && c(u, e) < 0) {
                    throw "Negative edge";
                }
#endif
                if (e.capacity > 0 && dis[v] > w + c(u, e)) {
                    dis[v] = w + c(u, e);
                    pre[v] = &e;
                    int at = heap.at(v);
                    if (at == -1) {
                        heap.push(v);
                    } else {
                        heap.siftUp(at);
                    }
                }
            }
        }
    };

    auto addOne = [&](int from, int id) {
        Edge& e = graph[from][id];
        int u = from;
        int v = e.to;
        ll curLen = c(u, e);
        if (e.capacity != 0) {
            e.capacity++;
            return;
        }
        dijkstra(v);
        if (dis[u] < inf && dis[u] + c(u, e) < 0) {
            e.reverseEdge(graph).capacity++;
            while (u != v) {
                Edge* x = pre[u];
                x->push(graph, 1);
                u = x->reverseEdge(graph).to;
            }
        } else {
            e.capacity++;
        }
        ll maxDis = 0;
        for (int i : range(n)) {
            if (dis[i] < inf) {
                maxim(maxDis, dis[i]);
            }
        }
        for (int i : range(n)) {
            p[i] += dis[i] < inf ? dis[i] : maxDis + abs(curLen);
        }
        dijkstra(n);
        for (int i : range(n)) {
            p[i] += dis[i] - p[n];
        }
    };

    addOne(sink, back);
    for (int i : RevRange(40)) {
        for (int j : range(n + 1)) {
            for (Edge& e : graph[j]) {
                e.capacity <<= 1;
            }
        }
        for (Edge* e : base) {
            if (e != nullptr && (e->capacity >> i & 1) == 1) {
                addOne(e->reverseEdge(orGraph).to, corresponding[e->id]);
            }
        }
    }

    ll minCost = 0;
    ll minFlow = graph[sink][back].flow(graph);
    for (Edge* e : base) {
        if (e == nullptr) {
            continue;
        }
        Edge& x = graph[e->reverseEdge(orGraph).to][corresponding[e->id]];
        minCost += x.flow(graph) * x.weight;
        e->push(orGraph, x.flow(graph));
    }
    return {minCost, minFlow};
}
