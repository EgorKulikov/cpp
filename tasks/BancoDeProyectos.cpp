#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class BancoDeProyectos {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto t = in.readIntArray(n);
        int m = *max_element(all(t));
        replace(all(t), m, 0);
        out.printLine(accumulate(all(t), ll(0)));
	}
};
