#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class InOrderOfSize {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto h = in.readIntArray(n);
        sort(all(h));
        out.print(h.back());
        if (n > 1) {
            out.print(' ');
        }
        out.printLine(vi(h.begin(), h.end() - 1));
	}
};
