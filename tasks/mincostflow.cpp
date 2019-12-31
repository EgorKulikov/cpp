#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/graph/graph.h"
#include "../lib/graph/mincost_flow.h"

//#pragma comment(linker, "/STACK:200000000")

class mincostflow {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int m = in.readInt();
        arri from, to, cap, cost;
        in.readArrays(m, from, to, cap, cost);
        decreaseByOne(from, to);

        Graph<WeightedFlowEdge<ll, ll>> graph(n);
        for (int i : range(m)) {
            graph.addEdge(from[i], to[i], cost[i], cap[i]);
        }
        auto answer = minCostFlow(graph, 0, n - 1);
        out.printLine(answer.second, answer.first);
	}
};
