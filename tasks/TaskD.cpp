#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

struct Trap {
    int l, r, d;

    Trap(int l, int r, int d) : l(l), r(r), d(d) {}
};

bool operator <(const Trap& a, const Trap& b) {
    return a.l < b.l;
}

class TaskD {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int m = in.readInt();
        int n = in.readInt();
        int k = in.readInt();
        int t = in.readInt();
        auto a = in.readIntArray(m);
        vector<Trap> traps;
        traps.reserve(k);
        for (int i = 0; i < k; ++i) {
            int l = in.readInt();
            int r = in.readInt();
            int d = in.readInt();
            traps.emplace_back(l, r, d);
        }

        sort(all(traps));
        int addWalk = (t - (n + 1)) / 2;
        sort(all(a));
        int left = 0;
        int right = m;
        while (left < right) {
            int mid = (left + right) / 2;
            int remaining = addWalk;
            int start = 0;
            int end = 0;
            for (const auto& trap : traps) {
                if (trap.d > a[mid]) {
                    if (trap.l - 1 > end) {
                        remaining -= end - start;
                        start = trap.l - 1;
                    }
                    maxim(end, trap.r);
                }
            }
            remaining -= end - start;
            if (remaining < 0) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        out.printLine(m - left);
	}
};
