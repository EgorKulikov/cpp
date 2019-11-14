#include "../lib/io/input.h"
#include "../lib/io/output.h"

class TheBigBang {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int a0 = in.readInt();
        ll max = ll(1000000000);
        max *= max;
        vector<ll> a(1, a0);
        while (a.size() < n && a.back() <= max) {
            if ((a.size() & 1) == 1) {
                a.push_back(a.back() * 3);
            } else {
                a.push_back(a[a.size() - 2] * 8);
            }
        }
        if (a.back() > max) {
            a.pop_back();
        }
        vector<ll> vals;
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < j; k++) {
                    if (a[i] + a[j] + a[k] <= max) {
                        vals.push_back(a[i] + a[j] + a[k]);
                    }
                }
            }
        }
        
        int q = in.readInt();
        for (int i = 0; i < q; ++i) {
            ll x = in.readLong();
            int ans = 0;
            for (long j : vals) {
                if (x % j == 0) {
                    ans++;
                }
            }
            out.printLine(ans);
        }
	}
};
