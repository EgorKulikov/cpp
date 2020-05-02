#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/graph/graph.h"
#include "../lib/graph/edges/biedge.h"
#include "../lib/recursive_function.h"

class FLISOnTree {
public:
	void solve() {
	    int n = in.readInt();
	    auto a = in.readIntArray(n);
	    arri u, v;
	    in.readArrays(n - 1, u, v);
	    decreaseByOne(u, v);

	    Graph<BiEdge> graph(n);
	    for (int i : range(n - 1)) {
	        graph.addEdge(u[i], v[i]);
	    }
	    arri answer(n);
	    vi seq;
	    RecursiveFunction dfs = [&](const auto& self, int vert, int last) -> void {
	        int pos = lower_bound(all(seq), a[vert]) - seq.begin();
	        int was = pos == seq.size() ? -1 : seq[pos];
	        if (pos < seq.size()) {
                seq[pos] = a[vert];
            } else {
	            seq.push_back(a[vert]);
	        }
	        answer[vert] = seq.size();
	        for (auto* e : graph[vert]) {
	            int next = e->to;
	            if (next == last) {
	                continue;
	            }
	            self(next, vert);
	        }
	        if (was == -1) {
	            seq.pop_back();
	        } else {
	            seq[pos] = was;
	        }
	    };
	    dfs(0, -1);
	    for (int i : answer) {
	        out.printLine(i);
	    }
	}
};
