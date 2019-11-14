#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/algo.h"

class TheInfinityLand {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        vector<ll> l;
        vector<ll> r;

        tie(l, r) = in.readArrays<ll, ll>(n);
        int x = in.readInt();
        int y = in.readInt();
        vector<ll> interesting;
        addAll(interesting, l);
        for (int i = 0; i < n; i++) {
            interesting.push_back(r[i] + 1);
        }
        sort(all(interesting));
        unique(interesting);
        vi delta(interesting.size());
        for (int i = 0; i < n; i++) {
            int at = lower_bound(all(interesting), l[i]) - interesting.begin();
            delta[at]++;
            at = lower_bound(all(interesting), r[i] + 1) - interesting.begin();
            delta[at]--;
        }
        int current = 0;
        ll answer = 0;
        for (int i = 0; i + 1 < interesting.size(); i++) {
            current += delta[i];
            if (current >= x && current <= y) {
                answer += interesting[i + 1] - interesting[i];
            }
        }
        out.printLine(answer);
	}
};
