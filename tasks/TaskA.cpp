#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class TaskA {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int a = in.readInt();
        int b = in.readInt();
        int c = in.readInt();
        int r = in.readInt();

        if (a > b) {
            swap(a, b);
        }
        if (b <= c) {
            int will = min(r, c - a) - min(r, c - b);
            out.printLine(b - a - will);
            return;
        }
        if (a >= c) {
            int will = min(r, b - c) - min(r, a - c);
            out.printLine(b - a - will);
            return;
        }
        int will = min(r, b - c) + min(r, c - a);
        out.printLine(b - a - will);
	}
};
