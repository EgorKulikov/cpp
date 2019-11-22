#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class FixedParities {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto r = in.readIntArray(n);
        auto c = in.readIntArray(n);
        bool sameRow = true;
        bool sameCol = true;
        vi rowId(n);
        vi colId(n);
        auto process = [&](vi& r, vi& rowId, bool& sameRow) -> void {
            for (int i = 1; i < n; i++) {
                if ((r[i] & 1) != (r[i - 1] & 1)) {
                    sameRow = false;
                    rowId[i] = rowId[i - 1] + 1;
                } else {
                    rowId[i] = rowId[i - 1];
                }
            }
        };
        process(r, rowId, sameRow);
        process(c, colId, sameCol);
        int q = in.readInt();
        for (int i = 0; i < q; i++) {
            int r1 = in.readInt() - 1;
            int c1 = in.readInt() - 1;
            int r2 = in.readInt() - 1;
            int c2 = in.readInt() - 1;
            if (sameRow) {
                out.printLine(colId[c1] == colId[c2] ? "YES" : "NO");
            } else if (sameCol) {
                out.printLine(rowId[r1] == rowId[r2] ? "YES" : "NO");
            } else {
                out.printLine(((r[r1] + c[c1]) & 1) == ((r[r2] + c[c2]) & 1) ? "YES" : "NO");
            }
        }
	}
};
