#include "../lib/io/input.h"
#include "../lib/io/output.h"

class TaskC {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int a = in.readInt();
        int d = in.readInt();
        
        int r = d / a;
        int q = d % a;
        out.printLine(a + (q + r - 1) / r);
	}
};
