#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/graph/graph.h"

//#pragma comment(linker, "/STACK:200000000")

class TaskE {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        arri a, b, c;
        in.readArrays(n - 2, a, b, c);
        decreaseByOne(a, b, c);

        map<pii, int> id;
        Graph<BiEdge> graph(n - 2);
        auto getp = [](int x, int y) -> pii {
            return {min(x, y), max(x, y)};
        };
        for (int i : range(n - 2)) {
            arr<pii> edges = {getp(a[i], b[i]), getp(b[i], c[i]), getp(a[i], c[i])};
            for (const auto& p : edges) {
                if (id.count(p)) {
                    graph.addEdge(i, id[p]);
                    id.erase(p);
                } else {
                    id[p] = i;
                }
            }
        }
        vi q;
        function<void(int, int, Graph<BiEdge>&, vi&)> dfs = [&](int vert, int last, Graph<BiEdge>& graph, vi& q) {
            for (auto* e : graph[vert]) {
                int next = e->to;
                if (next != last) {
                    dfs(next, vert, graph, q);
                }
            }
            q.push_back(vert + 1);
        };
        dfs(0, -1, graph, q);
        Graph<BiEdge> vGraph(n);
        bool zeroEdge = false;
        for (const auto& p : id) {
            const pii& edge = p.first;
            if (edge.first == 0 || edge.second == 0) {
                if (zeroEdge) {
                    continue;
                }
                zeroEdge = true;
            }
            vGraph.addEdge(edge.first, edge.second);
        }
        vi p;
        dfs(0, -1, vGraph, p);
        out.printLine(p);
        out.printLine(q);
	}
};
