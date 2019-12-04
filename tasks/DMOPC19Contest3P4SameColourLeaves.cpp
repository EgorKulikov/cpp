#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/graph/graph.h"
#include "../lib/numbers/modulo.h"

//#pragma comment(linker, "/STACK:200000000")

class DMOPC19Contest3P4SameColourLeaves {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        string color = in.readString();
        vi u, v;
        in.readArrays(n - 1, u, v);
        decreaseByOne(u, v);

        Graph<BidirectionalEdge> graph(n);
        for (int i = 0; i < n - 1; ++i) {
            graph.addEdge(new BidirectionalEdge(u[i], v[i]));
        }
        ModuloInt answer = 0;
        vector<ModuloInt> blue(n);
        vector<ModuloInt> red(n);
        function<void(int, int)> dfs = [&](int vertex, int last) -> void {
            blue[vertex] = 1;
            red[vertex] = 1;
            ModuloInt delta = 1;
            bool isBlue = color[vertex] == 'B';
            for (auto edge : graph.edges[vertex]) {
                int to = edge->to;
                if (to == last) {
                    continue;
                }
                dfs(to, vertex);
                blue[vertex] *= 1 + blue[to];
                red[vertex] *= 1 + red[to];
                if (isBlue) {
                    delta += red[to];
                } else {
                    delta += blue[to];
                }
            }
            answer += red[vertex] + blue[vertex] - delta;
            if (isBlue) {
                red[vertex] -= 1;
            } else {
                blue[vertex] -= 1;
            }
        };
        dfs(0, -1);
        out.printLine(answer);
	}
};
