#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class day1 {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        ll answer = 0;
        while (!in.isExhausted()) {
            ll mass = in.readLong();
            while (true) {
                ll next = mass / 3 - 2;
                if (next <= 0) {
                    break;
                }
                answer += next;
                mass = next;
            }
        }
        ll current = answer;
        out.printLine(answer);
	}
};
