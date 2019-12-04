#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/collections/dsu.h"

//#pragma comment(linker, "/STACK:200000000")
mt19937 rng(34564);

struct edge {
    int from, to, id;

    edge(int from, int to, int id) : from(from), to(to), id(id) {}
};

class DMOPC19Contest3P6TST {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int m = in.readInt();
        vector<edge> edges;
        for (int i = 0; i < m; ++i) {
            int from = in.readInt() - 1;
            int to = in.readInt() - 1;
            edges.emplace_back(from, to, i);
        }
        
        if (m < 3 * (n - 1)) {
            out.printLine(-1);
            return;
        }

        auto time = clock();

        int limit = 5 * CLOCKS_PER_SEC / 4;
        string answer(m, '0');
        auto random = [](int mod) -> int {
            return rng() % mod;
        };
        while (clock() - time < limit) {
            random_shuffle(all(edges), random);
            DSU first(n);
            DSU second(n);
            DSU third(n);
            for (const auto& e : edges) {
                if (second.getSetCount() > first.getSetCount() && second.getSetCount() >= third.getSetCount() && second.join(e.from, e.to)) {
                    answer[e.id] = '2';
                } else if (third.getSetCount() > first.getSetCount() && third.getSetCount() > second.getSetCount() && third.join(e.from, e.to)) {
                    answer[e.id] = '3';
                } else if (first.join(e.from, e.to)) {
                    answer[e.id] = '1';
                } else if (third.getSetCount() < second.getSetCount() && third.join(e.from, e.to)) {
                    answer[e.id] = '3';
                } else if (second.join(e.from, e.to)) {
                    answer[e.id] = '2';
                } else if (third.join(e.from, e.to)) {
                    answer[e.id] = '3';
                } else {
                    answer[e.id] = '0';
                }
            }
            if (third.getSetCount() == 1 && second.getSetCount() == 1 && first.getSetCount() == 1) {
                out.printLine(answer);
                return;
            }
        }
        out.printLine(-1);
	}
};
