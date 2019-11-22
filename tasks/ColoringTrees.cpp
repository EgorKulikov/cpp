#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/graph/graph.h"

//#pragma comment(linker, "/STACK:200000000")

class ColoringTrees {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int k = in.readInt();
        vi u, v;
        in.readArrays(n - 1, u, v);
        auto term = in.readIntArray(k);
        decreaseByOne(u, v, term);
        Graph<BidirectionalEdge> graph(n);
        for (int i = 0; i < n - 1; ++i) {
            graph.addEdge(new BidirectionalEdge(u[i], v[i]));
        }
        int answer = n;
        vector<bool> isTerm(n);
        for (int i : term) {
            isTerm[i] = true;
        }
        function<bool(int, int)> dfs = [&](int vertex, int last) -> bool {
            bool res = isTerm[vertex];
            for (auto edge : graph.edges[vertex]) {
                if (edge->to != last) {
                    res |= dfs(edge->to, vertex);
                }
            }
            if (!res) {
                answer--;
            }
            return res;
        };
        dfs(term[0], -1);
        out.printLine(answer);
	}
};
