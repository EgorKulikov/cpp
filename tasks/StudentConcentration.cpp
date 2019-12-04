#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class StudentConcentration {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto c = in.readIntArray(n);
        ll s = accumulate(all(c), ll(0));
        ll mi = *min_element(all(c));
        ll ma = *max_element(all(c));
        if (s - n * mi < n * ma - s) {
            out.printLine("Low");
        } else if (s - n * mi > n * ma - s) {
            out.printLine("High");
        } else {
            out.printLine("Middle");
        }
	}
};
