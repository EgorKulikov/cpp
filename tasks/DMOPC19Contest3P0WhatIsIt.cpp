#include "../lib/io/input.h"
#include "../lib/io/output.h"

//#pragma comment(linker, "/STACK:200000000")

class DMOPC19Contest3P0WhatIsIt {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        auto a = in.readIntArray(10);
        bool arithmetic = true;
        bool geometric = true;
        for (int i = 1; i < 9; i++) {
            if (2 * a[i] != a[i - 1] + a[i + 1]) {
                arithmetic = false;
            }
            if (ll(a[i]) * a[i] != ll(a[i - 1]) * a[i + 1]) {
                geometric = false;
            }
        }
        if (arithmetic) {
            if (geometric) {
                out.printLine("both");
            } else {
                out.printLine("arithmetic");
            }
        } else {
            if (geometric) {
                out.printLine("geometric");
            } else {
                out.printLine("neither");
            }
        }
	}
};
