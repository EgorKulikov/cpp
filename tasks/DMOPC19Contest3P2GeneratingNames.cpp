#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/numbers/numbers.h"
#include "../lib/algo.h"

//#pragma comment(linker, "/STACK:200000000")

class DMOPC19Contest3P2GeneratingNames {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int k = in.readInt();
        string s = in.readString();

        vi qty(26);
        int wildcards = 0;
        for (char c : s) {
            if (c == '*') {
                wildcards++;
            } else {
                qty[c - 'a']++;
            }
        }
        auto c = makeArray(n + 1, n + 1, ll(0));
        for (int i = 0; i <= n; ++i) {
            c[i][0] = 1;
            for (int j = 1; j <= i; ++j) {
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
            }
        }
        ll answer = 0;
        auto go = [&]() -> void {
            ll cur = 1;
            int rem = n;
            for (int i : qty) {
                cur *= c[rem][i];
                rem -= i;
            }
            answer += cur;
        };
        if (wildcards == 0) {
            go();
        } else if (wildcards == 1) {
            for (int i = 0; i < 26; ++i) {
                qty[i]++;
                go();
                qty[i]--;
            }
        } else {
            for (int i = 0; i < 26; ++i) {
                qty[i]++;
                for (int j = 0; j <= i; ++j) {
                    qty[j]++;
                    go();
                    qty[j]--;
                }
                qty[i]--;
            }
        }
        out.printLine(answer);
	}
};
