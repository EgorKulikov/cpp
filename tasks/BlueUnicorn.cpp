#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class BlueUnicorn {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto a = in.readArray<ll>(n);
        ll answer = 0;
        for (ll i : a) {
            answer ^= i;
        }
        out.printLine(answer);
	}
};
