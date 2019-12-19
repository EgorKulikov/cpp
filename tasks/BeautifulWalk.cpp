#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/graph/graph.h"
#include "../lib/collections/queue.h"
#include "../lib/range/rev_range.h"
#include "../lib/algo.h"

//#pragma comment(linker, "/STACK:200000000")

class BeautifulWalk {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int m = in.readInt();
        arri a, b;
        in.readArrays(m, a, b);
        decreaseByOne(a, b);

        using edge = BaseEdge;
        Graph<edge> graph(n);
        for (int i : range(m)) {
            graph.addEdge(new edge(a[i], b[i]));
        }
        arr2d<int> length(n, n);
        arr2d<int> last(n, n, -1);
        arri reach(n);
        for (int i : range(n)) {
            length(i, i) = 0;
            last(i, i) = -2;
            que<int> q;
            q.push(i);
            reach[i] = 1;
            while (!q.empty()) {
                int vert = q.pop();
                for (edge* e : graph[vert]) {
                    int to = e->to;
                    if (last(i, to) == -1) {
                        last(i, to) = vert;
                        length(i, to) = length(i, vert) + 1;
                        q.push(to);
                        reach[i]++;
                    }
                }
            }
            for (int j : range(i)) {
                if (last(i, j) == -1 && last(j, i) == -1) {
                    out.printLine(-1);
                    return;
                }
            }
        }
        arr<vi> slices(n + 1, vi());
        for (int i : range(n)) {
            slices[reach[i]].push_back(i);
        }
        for (int x = 0; ; x++) {
            arr<bool> done(n, false);
            int cur = -1;
            vi answer;
            for (int i : RevRange(n + 1)) {
                if (slices[i].empty()) {
                    continue;
                }
                int rem = slices[i].size();
                if (cur == -1) {
                    if (slices[i].size() == x) {
                        out.printLine(-1);
                        return;
                    }
                    cur = slices[i][x];
                    done[cur] = true;
                    answer.push_back(cur + 1);
                    rem--;
                }
                while (rem > 0) {
                    int best = -1;
                    int dst = n + 1;
                    for (int j : slices[i]) {
                        if (!done[j] && length(cur, j) < dst) {
                            dst = length(cur, j);
                            best = j;
                        }
                    }
                    vi part;
                    int at = best;
                    while (at != cur) {
                        part.push_back(at + 1);
                        at = last(cur, at);
                    }
                    reverse(all(part));
                    addAll(answer, all(part));
                    rem--;
                    cur = best;
                    done[cur] = true;
                }
            }
            if (answer.size() - 1 <= n * n / 4) {
                out.printLine(answer.size() - 1, answer);
                return;
            }
        }
	}
};
