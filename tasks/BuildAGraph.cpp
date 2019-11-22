#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class BuildAGraph {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        out.printLine(n >= 6 ? "Yes" : "No");
	}
};
