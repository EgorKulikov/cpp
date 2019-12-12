#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/numbers/modulo.h"
#include "../lib/numbers/prime_fft.h"
#include "../lib/algo.h"

//#pragma comment(linker, "/STACK:200000000")

class BinomialFever {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        mod = MODF;
        initPrimeFFT();
        prime_fft::aa.resize(2000000);
        prime_fft::bb.resize(2000000);

        int n = in.readInt();
        modint p = in.readInt();
        int r = in.readInt();
        auto work = makeArray(2, 2 * r, modint(0));
        function<void(int, int, int)> build = [&](int from, int to, int side) {
            if (from + 1 == to) {
                work[side][2 * from] = -from;
                work[side][2 * from + 1] = 1;
                return;
            }
            int mid = (from + to) / 2;
            build(from, mid, 1 - side);
            build(mid, to, 1 - side);
            multiply(work[1 - side].begin() + (2 * from), work[1 - side].begin() + (from + mid + 1),
                    work[1 - side].begin() + (2 * mid), work[1 - side].begin() + (mid + to + 1),
                    work[side].begin() + (2 * from));
        };
#ifdef LOCAL
        ll time = clock();
#endif
        build(0, r, 0);
#ifdef LOCAL
        cerr << "built " << clock() - time << endl;
#endif
        vector<modint>& poly = work[0];
        modint answer = 0;
        function<modint(modint, modint&, int)> sump = [&](modint base, modint& power, int exp) -> modint {
            if (exp == 0) {
                power = 1;
                return 0;
            }
            if ((exp & 1) == 0) {
                auto val = sump(base, power, exp >> 1);
                auto res = val * (1 + power);
                power *= power;
                return res;
            } else {
                auto val = sump(base, power, exp - 1);
                power *= base;
                return val * base + 1;
            }
        };
        modint pw = 1;
        modint temp = 0;
        for (int i : Range(r + 1)) {
            answer += sump(pw, temp, n + 1) * poly[i];
            pw *= p;
        }
        modint fact = 1;
        for (int i = 2; i <= r; i++) {
            fact *= i;
        }
        fact = power(fact, mod - 2);
        answer *= fact;
        out.printLine(answer);
	}
};
