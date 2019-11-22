#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/numbers/primes.h"
#include "../lib/algo.h"
#include "../lib/numbers/bigint.h"
#include "../lib/numbers/numbers.h"

//#pragma comment(linker, "/STACK:200000000")

class HiddenSquares {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        if (n == 1) {
            out.printLine(0, 2);
            return;
        }
        auto p = primes(1000);
        auto done = makeArray(n, n, false);
        int notDone = n * n;
        BigInt x = 0;
        BigInt y = 0;
        BigInt mod = 1;
        for (int i : p) {
            if (notDone == 0) {
                break;
            }
            vector<pii> cand;
            int pts = 0;
            for (int j = 0; j < i && j < n; j++) {
                for (int k = 0; k < i && k < n; k++) {
                    int cur = 0;
                    for (int l = j; l < n; l += i) {
                        for (int m = k; m < n; m += i) {
                            if (!done[l][m]) {
                                cur++;
                            }
                        }
                    }
                    if (cur > pts) {
                        pts = cur;
                        cand.clear();
                    }
                    if (cur == pts) {
                        cand.emplace_back(j, k);
                    }
                }
            }
            bool first = true;
            BigInt nx;
            BigInt ny;
            int a;
            int b;
            for (auto c : cand) {
                auto cx = findCommon(x, mod, (i - c.first) % i, i);
                auto cy = findCommon(y, mod, (i - c.second) % i, i);
                if (first || cx + cy < nx + ny) {
                    nx = cx;
                    ny = cy;
                    a = c.first;
                    b = c.second;
                }
            }
            x = nx;
            y = ny;
            mod *= i;
            for (int j = a; j < n; j += i) {
                for (int k = b; k < n; k += i) {
                    if (!done[j][k]) {
                        notDone--;
                        done[j][k] = true;
                    }
                }
            }
        }
        out.printLine(x, y);
	}
};
