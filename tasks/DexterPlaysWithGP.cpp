#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
#include "../lib/numbers/modulo.h"

//#pragma comment(linker, "/STACK:200000000")

class DexterPlaysWithGP {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int r = in.readInt();
        int s = in.readInt();
        int p = in.readInt();

        mod = p;
        modint alpha = r;
        modint beta = (alpha - 1) * s + 1;
        if (beta == 0) {
            out.printLine(-1);
            return;
        }
        int answer = beta.log(alpha);
        if (answer == 0) {
            answer = p - 1;
        }
/*        modint check = 0;
        modint add = 1;
        for (int i : range(answer)) {
            check += add;
            add *= alpha;
        }
        if (check != s) {
            exit(1);
        }*/
        out.printLine(answer);
	}
};
