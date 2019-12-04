#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

vector<ll> ways(7500);
bool done = false;

class CoinChange {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        if (!done) {
            ways[0] = 1;
            for (int i : {1, 5, 10, 25, 50}) {
                for (int j : Range(i, 7500)) {
                    ways[j] += ways[j - i];
                }
            }
            done = true;
        }
        
        in.skipWhitespace();
        if (in.isExhausted()) {
            return;
        }
        out.printLine(ways[in.readInt()]);
	}
};
