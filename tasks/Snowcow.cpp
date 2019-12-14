#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/graph/graph.h"
#include "../lib/collections/interval_tree.h"
#include "../lib/graph/dfs_order.h"

//#pragma comment(linker, "/STACK:200000000")

class Snowcow {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int q = in.readInt();
        arri a, b;
        in.readArrays(n - 1, a, b);
        arri type(q);
        arri x(q);
        arri c(q);
        for (int i : Range(q)) {
            type[i] = in.readInt();
            x[i] = in.readInt() - 1;
            if (type[i] == 1) {
                c[i] = in.readInt() - 1;
            }
        }
        decreaseByOne(a, b);
        typedef BiEdge edge;
        Graph<edge> graph(n);
        for (int i : Range(n - 1)) {
            graph.addEdge(new edge(a[i], b[i]));
        }
        DFSOrder<edge> order(graph);
        unordered_map<int, set<int> > changes;
        auto sum = [](ll a, ll b) -> ll { return a + b; };
        IntervalTree<ll, ll> tree(n, sum, sum, [](ll val, ll delta, int from, int to) -> ll {
            return val + delta * (to - from);
        });
        arri end(n);
        for (int i = 0; i < n; i++) {
            end[order.position[i]] = order.end[i];
        }
        for (int i : Range(q)) {
            if (type[i] == 2) {
                out.printLine(tree.query(order.position[x[i]], order.end[x[i]] + 1));
            } else {
                set<int>& m = changes[c[i]];
                auto it = m.lower_bound(order.position[x[i]]);
                if (it != m.end() && *it == order.position[x[i]]) {
                    continue;
                }
                if (it != m.begin()) {
                    auto jit = it;
                    jit--;
                    if (end[*jit] >= order.position[x[i]]) {
                        continue;
                    }
                }
                while (it != m.end() && *it <= order.end[x[i]]) {
                    tree.update(*it, end[*it] + 1, -1);
                    it = m.erase(it);
                }
                tree.update(order.position[x[i]], order.end[x[i]] + 1, 1);
                m.insert(order.position[x[i]]);
            }
        }
	}
};
