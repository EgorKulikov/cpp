#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/algo.h"
#include "../lib/range/rev_range.h"

//#pragma comment(linker, "/STACK:200000000")

class Pieaters {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int m = in.readInt();
        arri w, l, r;
        in.readArrays(m, w, l, r);
        decreaseByOne(l, r);
        auto b = makeArray(n, n, 0);
        for (int i : Range(m)) {
            b[l[i]][r[i]] = w[i];
        }
        auto bb = makeArray(n, n, n, 0);
        for (int i : RevRange(n)) {
            for (int j : Range(i, n)) {
                for (int k : Range(i, j + 1)) {
                    bb[i][j][k] = max(b[i][j], max(i < n - 1 ? bb[i + 1][j][k] : 0, j > 0 ? bb[i][j - 1][k] : 0));
                }
            }
        }
        auto ans = makeArray(n, n, -1);
        function<int(int, int)> go = [&](int f, int t) -> int {
            if (f > t) {
                return 0;
            }
            if (ans[f][t] != -1) {
                return ans[f][t];
            }
            ans[f][t] = b[f][t];
            for (int i : Range(f, t + 1)) {
                maxim(ans[f][t], bb[f][t][i] + go(f, i - 1) + go(i + 1, t));
            }
            return ans[f][t];
        };
        out.printLine(go(0, n - 1));
	}
};
