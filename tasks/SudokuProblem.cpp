#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/algo.h"

//#pragma comment(linker, "/STACK:200000000")

class SudokuProblem {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto table = in.readTable<int>(n, n);
        int small = int(round(sqrt(n)));

        vi rows(n);
        vi cols(n);
        auto sq = makeArray(small, small, 0);
        for (int i : Range(n)) {
            for (int j : Range(n)) {
                int c = table[i][j] - 1;
                rows[i] |= 1 << c;
                cols[j] |= 1 << c;
                sq[i / small][j / small] |= 1 << c;
            }
        }
        int expected = (1 << n) - 1;
        if (count(all(rows), expected) == n && count(all(cols), expected) == n && count(all(sq), vi(small, expected)) == small) {
            out.printLine("yes");
        } else {
            out.printLine("no");
        }
	}
};
