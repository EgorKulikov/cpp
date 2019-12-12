#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/numbers/modulo.h"
#include "../lib/numbers/prime_fft.h"

//#pragma comment(linker, "/STACK:200000000")

class BinomialFever {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        mod = MODF;
        initPrimeFFT();

        int n = in.readInt();
        ModuloInt p = in.readInt();
        int r = in.readInt();
        function<vector<ModuloInt>(int, int)> build = [&](int from, int to) -> vector<ModuloInt> {
            if (from + 1 == to) {
                return {ModuloInt(-from), ModuloInt(1)};
            }
            int mid = (from + to) / 2;
            auto left = build(from, mid);
            auto right = build(mid, to);
            if (from == 0 && to == r) {
#ifdef LOCAL
                cerr << "start build" << endl;
#endif
            }
            return multiply(left, right);
        };
        auto poly = build(0, r);
#ifdef LOCAL
        cerr << "end build" << endl;
#endif
        ModuloInt answer = 0;
        function<ModuloInt(ModuloInt, ModuloInt&, int)> sump = [&](ModuloInt base, ModuloInt& power, int exp) -> ModuloInt {
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
        ModuloInt pw = 1;
        ModuloInt temp = 0;
        for (int i : Range(poly.size())) {
            answer += sump(pw, temp, n + 1) * poly[i];
            pw *= p;
        }
        ModuloInt fact = 1;
        for (int i = 2; i <= r; i++) {
            fact *= i;
        }
        fact = power(fact, mod - 2);
        answer *= fact;
        out.printLine(answer);
	}
};
