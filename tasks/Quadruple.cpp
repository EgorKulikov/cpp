#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/numbers/modulo.h"

//#pragma comment(linker, "/STACK:200000000")

class Quadruple {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        ModuloInt a = in.readInt();
        ModuloInt b = in.readInt();
        ModuloInt c = in.readInt();
        ModuloInt d = in.readInt();
        
        for (int i : Range(n)) {
            ModuloInt oa = a;
            a -= b;
            b -= c;
            c -= d;
            d -= oa;
        }
        out.printLine(a, b, c, d);
	}
};
