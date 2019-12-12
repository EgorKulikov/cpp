#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/numbers/modulo.h"
#include "../lib/numbers/number_iterator.h"
#include "../lib/algo.h"
#include "../lib/numbers/numbers.h"
#include "../lib/range/rev_range.h"

//#pragma comment(linker, "/STACK:200000000")

class ScoringPairs {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        ll l = in.readLong();
        ll r = in.readLong();
        modint answer = 0;
//        Combinations<modint> c(40);
        auto c = makeArray(21, 21, 0);
        for (int i : Range(21)) {
            c[i][0] = 1;
            for (int j : Range(1, i + 1)) {
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
            }
        }
        vi aq(10);
        vi bq(10);
        vi aa(10);
        vi ba(10);
        auto resA = makeArray(21, 21, modint(0));
        auto resB = makeArray(21, 21, modint(0));
        auto qA = makeArray(21, 21, modint(0));
        auto qB = makeArray(21, 21, modint(0));
        iterate(l, r, [&](ll aPrefix, int aDigs) {
            fill(all(aq), 0);
            ll ap = aPrefix;
            while (ap != 0) {
                aq[ap % 10]++;
                ap /= 10;
            }
            for (int i : RevRange(9)) {
                aa[i] = aa[i + 1] + aq[i + 1];
            }
            iterate(l, r, [&](ll bPrefix, int bDigs) {
                fill(all(bq), 0);
                ll bp = bPrefix;
                while (bp != 0) {
                    bq[bp % 10]++;
                    bp /= 10;
                }

                for (int i : RevRange(9)) {
                    ba[i] = ba[i + 1] + bq[i + 1];
                }

                for (int i : Range(aDigs + 1)) {
                    for (int j : Range(bDigs + 1)) {
                        resA[i][j] = 0;
                        qA[i][j] = modint(c[aDigs][i]) * c[bDigs][j];
                    }
                }
                for (int i : Range(1, 10)) {
                    for (int j : Range(aDigs + 1)) {
                        for (int k : Range(bDigs + 1)) {
                            resB[j][k] = 0;
                            qB[j][k] = 0;
                            for (int l : Range(j, aDigs + 1)) {
                                int raBefore = l + aa[i] + aq[i];
                                int raAfter = j + aa[i];
                                int rb = k + ba[i] + bq[i];
                                int delta = -(min(raBefore, rb) - min(raAfter, rb) - max(raBefore, rb) + max(raAfter, rb));
//                                const modint &cc = c.c(l, j);
                                resB[j][k] += c[l][j] * (delta * i * qA[l][k] + resA[l][k]);
                                qB[j][k] += c[l][j] * qA[l][k];
                            }
                        }
                    }
                    for (int j : Range(bDigs + 1)) {
                        for (int k : Range(aDigs + 1)) {
                            resA[k][j] = 0;
                            qA[k][j] = 0;
                            for (int l : Range(j, bDigs + 1)) {
                                int raBefore = l + ba[i] + bq[i];
                                int raAfter = j + ba[i];
                                int rb = k + aa[i];
                                int delta = -(min(raBefore, rb) - min(raAfter, rb) - max(raBefore, rb) + max(raAfter, rb));
//                                const modint &cc = c.c(l, j);
                                resA[k][j] += c[l][j] * (delta * i * qB[k][l] + resB[k][l]);
                                qA[k][j] += c[l][j] * qB[k][l];
                            }
                        }
                    }
                }
                answer += resA[0][0];
            });
        });
        out.printLine(answer);
	}
};
