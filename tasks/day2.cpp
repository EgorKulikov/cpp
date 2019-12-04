#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class day2 {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        string input = in.readString();
        replace(all(input), ',', ' ');
        istringstream str(input);
        Input sin(str);
        vector<ll> mem;
        while (!sin.isExhausted()) {
            mem.push_back(sin.readInt());
        }

        auto origMem = mem;

        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 100; ++j) {
                bool error = false;
                mem = origMem;
                mem[1] = i;
                mem[2] = j;

                int at = 0;
                while (true) {
                    if (mem[at] == 99) {
                        break;
                    }
                    if (mem[at] == 1) {
                        mem[mem[at + 3]] = mem[mem[at + 1]] + mem[mem[at + 2]];
                    } else if (mem[at] == 2) {
                        mem[mem[at + 3]] = mem[mem[at + 1]] * mem[mem[at + 2]];
                    } else {
                        error = true;
                        break;
                    }
                    at += 4;
                }

                if (!error && mem[0] == 19690720) {
                    out.printLine(100 * i + j);
                    return;
                }
            }
        }

	}
};
