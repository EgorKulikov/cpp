#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/numbers/numbers.h"

//#pragma comment(linker, "/STACK:200000000")

class TaskC {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int r = in.readInt();
        int b = in.readInt();
        int k = in.readInt();
        int g = gcd(r, b);
        r /= g;
        b /= g;
        if (r < b) {
            swap(r, b);
        }
        int has = (r - 2) / b + 1;
        out.printLine(has < k ? "OBEY" : "REBEL");
	}
};
