#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class MissingRunners {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto a = in.readIntArray(n - 1);
        out.printLine(n * (n + 1) / 2 - accumulate(all(a), 0));
	}
};
