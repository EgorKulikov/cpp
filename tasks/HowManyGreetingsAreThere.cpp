#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class HowManyGreetingsAreThere {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        ll v = in.readLong() + 2;
        out.printLine(v * (v - 1) / 2);
	}
};
