#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/numbers/modulo.h"

class ExpectedChange {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto a = in.readArray<char>(n);

        modint ans = solve(n, a);
        out.printLine(ans);
	}

    modint solve(int n, const arr<char>& a) const {
        arri bal(n + 1);
        bal[0] = n;
        for (int i : range(n)) {
            bal[i + 1] = bal[i];
            if (a[i] == ')') {
                bal[i + 1]--;
            } else {
                bal[i + 1]++;
            }
        }
        arri last(2 * n + 1, -1);
        last[n] = 0;
        ll answer = 0;
        for (int i : range(n)) {
            if (a[i] == ')') {
                int q = (i + 1 - last[bal[i + 1]]) / 2;
                answer += ll(q) * (n - i);
            }
            last[bal[i + 1]] = i + 1;
        }
        modint ans = answer;
        ans *= (modint(n) * (n + 1)).inverse() * 2;
        return ans;
    }
};
