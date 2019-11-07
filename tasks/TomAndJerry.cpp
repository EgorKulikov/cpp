#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/graph/graph.h"

class TomAndJerry {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        vi x;
        vi y;
        tie(x, y) = in.readArrays<int, int>(n * (n - 1) / 2);
        decreaseByOne(x, y);
        vi incoming(n);
        for (int i : y) {
            incoming[i]++;
        }
        int vertex = min_element(all(incoming)) - incoming.begin();
        Graph<SimpleEdge> graph(n);
        for (int i = 0; i < x.size(); i++) {
            graph.addEdge(new SimpleEdge(y[i], x[i]));
        }
        vector<bool> visited(n);
        visited[vertex] = true;
        queue<int> q;
        q.push(vertex);
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (auto edge : graph.edges[current]) {
                int next = edge->to;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        if (count(all(visited), true) >= 3) {
            out.printLine("NO");
        } else {
            out.printLine("YES");
        }
	}
};
