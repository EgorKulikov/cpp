#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/algo.h"

//#pragma comment(linker, "/STACK:200000000")

class TobaccoFieldsForever {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int r = in.readInt();
        int c = in.readInt();
        int q = in.readInt();
        auto v = in.readTable<int>(r, c);
        
        auto sums = makeArray(r + 1, c + 1, 0);
        for (int i : Range(r)) {
            for (int j : Range(c)) {
                maxim(v[i][j], 0);
                sums[i + 1][j + 1] = sums[i + 1][j] + sums[i][j + 1] - sums[i][j] + v[i][j];
            }
        }
        
        for (int i : Range(q)) {
            int x1 = in.readInt() - 1;
            int y1 = in.readInt() - 1;
            int x2 = in.readInt();
            int y2 = in.readInt();
            out.printLine(sums[x2][y2] + sums[x1][y1] - sums[x2][y1] - sums[x1][y2]);
        }
	}
};
