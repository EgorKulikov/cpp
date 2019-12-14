#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/numbers/modulo.h"
#include "../lib/algo.h"

//#pragma comment(linker, "/STACK:200000000")

class Treedepth {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int k = in.readInt();
        int m = in.readInt();

        mod = m;
        auto q = arr2d<arr<modint> >(n, n, arr<modint>());
        for (int i : Range(n)) {
            for (int j : Range(n - i)) {
                if (i == 0 && j == 0) {
                    q(i, j) = arr<modint>(1, 1);
                } else {
                    q(i, j) = arr<modint>(i * j + 1, 0);
                    if (i > 0) {
                        for (int k : Range(q(i - 1, j).size())) {
                            q(i, j)[k] += q[i - 1][j][k];
                        }
                    }
                    if (j > 0) {
                        for (int k : Range(q[i][j - 1].size())) {
                            q(i, j)[k + i] += q[i][j - 1][k];
                        }
                    }
                }
            }
        }
        vec<vec<arr<modint> > > res(n + 1);
        vec<vec<modint> > qq(n + 1);
        res[0] = vec<arr<modint> >(1);
        qq[0] = vec<modint>(1, 1);
        auto temp = arr2d<modint>(k + 1, n, modint(0));
        vec<modint> qtemp(k + 1);
        vec<modint> localq(k + 1);
        for (int i = 1; i <= n; i++) {
            res[i] = vec<arr<modint> >(min(k + 1, i * (i - 1) / 2 + 1));
            qq[i] = vec<modint>(res[i].size());
            for (auto& row : res[i]) {
                row = arr<modint>(i, 0);
            }
            for (int j : Range(i)) {
                for (int l : Range(res[i].size())) {
                    fill(temp[l].begin(), temp[l].begin() + i, 0);
                }
                fill(qtemp.begin(), qtemp.begin() + res[i].size(), 0);
                fill(localq.begin(), localq.begin() + res[i].size(), 0);
                for (int l : Range(res[j].size())) {
                    for (int m : Range(min(int(res[i - j - 1].size()), k - l + 1 - j))) {
                        qtemp[l + m + j] += qq[j][l] * qq[i - j - 1][m];
                        for (int n : Range(j)) {
                            temp[l + m + j][n] += res[j][l][n] * qq[i - j - 1][m];
                        }
                        for (int n : Range(i - j - 1)) {
                            temp[l + m + j][j + 1 + n] += res[i - j - 1][m][n] * qq[j][l];
                        }
                    }
                }
                for (int l : Range(j, res[i].size())) {
                    for (int m : Range(min(int(q[j][i - j - 1].size()), min(k, int(res[i].size()) - 1) - l + 1))) {
                        modint ways = qtemp[l] * q[j][i - j - 1][m];
                        qq[i][l + m] += ways;
                        localq[l + m] += ways;
                        for (int n : Range(i)) {
                            res[i][l + m][n] += temp[l][n] * q[j][i - j - 1][m] + ways;
                        }
                    }
                }
            }
        }
        out.printLine(res[n][k]);
	}
};
