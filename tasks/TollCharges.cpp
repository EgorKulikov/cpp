#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/graph/graph.h"

//#pragma comment(linker, "/STACK:200000000")

vector<ll> val;

class Predicate {
public:
    bool operator()(int a, int b) const {
        if (val[a] != val[b]) {
            return val[a] > val[b];
        }
        return a < b;
    }
};

class TollCharges {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int k = in.readInt();
        vi x, y, a, b;
        in.readArrays(n - 1, x, y, a, b);
        decreaseByOne(x, y);
        if (k == n - 1) {
            out.printLine(0);
            return;
        }
        Graph<IntWeightedEdge> graph(n);
        for (int i = 0; i < n - 1; ++i) {
            graph.addEdge(new IntWeightedEdge(x[i], y[i], b[i]));
            graph.addEdge(new IntWeightedEdge(y[i], x[i], a[i]));
        }
        val.resize(2 * n - 2);
        set<int, Predicate> all;
        vi qty(n);
        function<void(int, int)> dfs = [&](int vertex, int last) -> void {
            qty[vertex] = 1;
            for (auto edge : graph.edges[vertex]) {
                if (edge->to == last) {
                    continue;
                }
                dfs(edge->to, vertex);
                qty[vertex] += qty[edge->to];
                val[edge->id] = ll(qty[edge->to]) * edge->weight;
                all.insert(edge->id);
            }
        };
        dfs(0, -1);
        auto it = all.begin();
        ll sum = 0;
        for (int i : all) {
            sum += val[i];
        }
        set<int, Predicate> best;
        for (auto i = 0; i < k; i++) {
            sum -= val[*it];
            best.insert(*it);
            it++;
        }
        ll answer = sum;
        auto remove = [&](int id) {
            all.erase(id);
            sum -= val[id];
            if (best.count(id) == 1) {
                best.erase(id);
                sum += val[id];
                auto it = all.begin();
                if (!best.empty()) {
                    it = all.lower_bound(*best.rbegin());
                    it++;
                }
                best.insert(*it);
                sum -= val[*it];
            }
        };
        Predicate predicate;
        auto add = [&](int id) {
            all.insert(id);
            sum += val[id];
            if (!best.empty() && predicate(id, *best.rbegin())) {
                sum += val[*best.rbegin()];
                best.erase(*best.rbegin());
                best.insert(id);
                sum -= val[id];
            }
        };
        function<void(int, int)> dfs2 = [&](int vertex, int last) -> void {
            int eId = -1;
            if (last != -1) {
                for (auto edge : graph.edges[vertex]) {
                    if (edge->to == last) {
                        eId = edge->id;
                        val[edge->id] = ll(edge->weight) * (n - qty[vertex]);
                        add(edge->id);
                        break;
                    }
                }
            }
            minim(answer, sum);
            for (auto edge : graph.edges[vertex]) {
                if (edge->to == last) {
                    continue;
                }
                remove(edge->id);
                dfs2(edge->to, vertex);
                add(edge->id);
            }
            if (eId != -1) {
                remove(eId);
            }
        };
        dfs2(0, -1);
        out.printLine(answer);
	}
};
