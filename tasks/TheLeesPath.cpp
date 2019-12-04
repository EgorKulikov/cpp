#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/misc.h"

//#pragma comment(linker, "/STACK:200000000")

class TheLeesPath {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int f = in.readInt();
        int c = in.readInt();
        auto map = in.readTable<int>(f, c);

        int row = 0;
        int col = find(all(map[0]), 1) - map[0].begin();
        string dirs = "DRUL";
        int qty = 0;
        char last = 0;
        while (true) {
            bool found = false;
            for (int i : Range(4)) {
                int nRow = row + DX4[i];
                int nCol = col + DY4[i];
                if (isValidCell(nRow, nCol, f, c) && map[nRow][nCol] == map[row][col] + 1) {
                    if (dirs[i] != last) {
                        if (qty > 1) {
                            out.print(qty);
                        }
                        if (qty > 0) {
                            out.print(last);
                        }
                        last = dirs[i];
                        qty = 0;
                    }
                    qty++;
                    found = true;
                    row = nRow;
                    col = nCol;
                    break;
                }
            }
            if (!found) {
                break;
            }
        }
        if (qty > 1) {
            out.print(qty);
        }
        if (qty > 0) {
            out.print(last);
        }
        if (row == 0 || row == f - 1 || col == 0 || col == c - 1) {
            out.printLine(" E");
        } else {
            out.printLine(" NE");
        }
	}
};
