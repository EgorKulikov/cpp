#pragma once

#include "../general.h"
#include "graph.h"
#include "../collections/arr.h"
#include "../collections/queue.h"
#include "../range/rev_range.h"

template <class Edge>
vi topologicalSort(Graph<Edge>& graph) {
    vi result;
    int n = graph.vertexCount;
    result.reserve(n);
    arri degree(n, 0);
    for (int i = 0; i < n; ++i) {
        for (auto edge : graph[i]) {
            degree[edge->to]++;
        }
    }
    que<int> q;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int cur = q.pop();
        result.push_back(cur);
        for (auto edge : graph[cur]) {
            if (--degree[edge->to] == 0) {
                q.push(edge->to);
            }
        }
    }
    if (result.size() != n) {
        return vi(0);
    }
    return result;
}

template <class Edge>
void centroidDecomposition(Graph<Edge>& graph, const function<void(int, const arr<bool>&, const vi&)>& callback) {
    int n = graph.vertexCount;
    arr<bool> forb(n, false);
    arri size(n);
    function<void(int)> doWork = [&](int vert) {
        vi part;
        function<void(int, int)> dfs = [&](int vert, int last) {
            size[vert] = 1;
            part.push_back(vert);
            for (auto* e : graph[vert]) {
                int next = e->to;
                if (next == last || forb[next]) {
                    continue;
                }
                dfs(next, vert);
                size[vert] += size[next];
            }
        };
        dfs(vert, -1);
        int end = -1;
        for (int i : part) {
            if (2 * size[i] >= part.size()) {
                bool good = true;
                for (auto* e : graph[i]) {
                    int to = e->to;
                    if (!forb[to] && size[to] * 2 > part.size() && size[to] < size[i]) {
                        good = false;
                        break;
                    }
                }
                if (good) {
                    end = i;
                    break;
                }
            }
        }

        callback(end, forb, part);

        forb[end] = true;
        for (auto* e : graph[end]) {
            int to = e->to;
            if (!forb[to]) {
                doWork(to);
            }
        }
    };
    doWork(0);
}

pair<arri, Graph<BaseEdge>> stronglyConnectedComponents(Graph<BaseEdge>& graph) {
    int n = graph.vertexCount;
    vi order;
    arr<bool> visited(n, false);
    arri condensed(n);
    order.reserve(n);
    function<void(int)> firstDFS = [&](int vert) {
        if (visited[vert]) {
            return;
        }
        visited[vert] = true;
        for (auto* e : graph[vert]) {
            firstDFS(e->to);
        }
        order.push_back(vert);
    };
    for (int i : range(n)) {
        if (!visited[i]) {
            firstDFS(i);
        }
    }
    fill(all(visited), false);
    Graph<BaseEdge> result(0);
    int index = 0;
    arri next(n, -1);
    vi queue;
    int key;
    Graph<BaseEdge> gt(n);
    for (int i : range(n)) {
        for (auto* e : graph[i]) {
            gt.addEdge(e->to, i);
        }
    }
    function<void(int)> secondDFS = [&](int vert) {
        if (visited[vert]) {
            if (condensed[vert] != index) {
                if (next[condensed[vert]] != key) {
                    next[condensed[vert]] = key;
                    queue.push_back(condensed[vert]);
                }
            }
            return;
        }
        condensed[vert] = index;
        visited[vert] = true;
        for (auto* e : gt[vert]) {
            secondDFS(e->to);
        }
    };
    for (int i : RevRange(n)) {
        if (!visited[order[i]]) {
            key = i;
            queue.clear();
            secondDFS(order[i]);
            result.addVertices(1);
            for (int j : queue) {
                result.addEdge(j, index);
            }
            index++;
        }
    }
    return {condensed, graph};
}